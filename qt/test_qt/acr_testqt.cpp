#include "acr_testqt.h"

#include <QApplication>
#include <QByteArray>
#include <QColor>
#include <QDateTime>
#include <QFile>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QTemporaryDir>
#include <QTextEdit>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QVBoxLayout>

#include <cmath>
#include <cstring>
#include <functional>
#include <limits>
#include <vector>

#include "ACR/alignedbuffer.h"
#include "ACR/buffer.h"
#include "ACR/datetime.h"
#include "ACR/file.h"
#include "ACR/info.h"
#include "ACR/string.h"
#include "ACR/timer.h"
#include "ACR/varbuffer.h"

#include "ACR/public/public_alignedbuffer.h"
#include "ACR/public/public_blocks.h"
#include "ACR/public/public_bool.h"
#include "ACR/public/public_buffer.h"
#include "ACR/public/public_byte_order.h"
#include "ACR/public/public_bytes_and_flags.h"
#include "ACR/public/public_clock.h"
#include "ACR/public/public_config.h"
#include "ACR/public/public_count.h"
#include "ACR/public/public_dates_and_times.h"
#include "ACR/public/public_debug.h"
#include "ACR/public/public_decimal.h"
#include "ACR/public/public_file.h"
#include "ACR/public/public_filesystem.h"
#include "ACR/public/public_functions.h"
#include "ACR/public/public_heap.h"
#include "ACR/public/public_info.h"
#include "ACR/public/public_int.h"
#include "ACR/public/public_math.h"
#include "ACR/public/public_memory.h"
#include "ACR/public/public_string.h"
#include "ACR/public/public_timer.h"
#include "ACR/public/public_unique_strings.h"
#include "ACR/public/public_units.h"
#include "ACR/public/public_varbuffer.h"
#include "ACR/public/public_version.h"

namespace
{

struct TestCase
{
    QString name;
    std::function<bool()> run;
};

struct TestSuite
{
    QString header;
    QString description;
    std::vector<TestCase> checks;
};

struct MemoryFile
{
    QByteArray data;
    ACR_Length_t position;
};

static TestCase check(const QString &name, const std::function<bool()> &run)
{
    return TestCase{name, run};
}

static ACR_Length_t memoryFilePosition(void *userData)
{
    return static_cast<MemoryFile *>(userData)->position;
}

static ACR_Info_t memoryFileSeek(
    ACR_Length_t moveBy,
    ACR_Info_t fromPosition,
    void *userData)
{
    MemoryFile *file = static_cast<MemoryFile *>(userData);
    const ACR_Length_t length = static_cast<ACR_Length_t>(file->data.size());

    if (fromPosition == ACR_INFO_FIRST)
    {
        if (moveBy > length)
        {
            return ACR_INFO_ERROR;
        }
        file->position = moveBy;
        return ACR_INFO_OK;
    }

    if (fromPosition == ACR_INFO_CURRENT)
    {
        if (moveBy > length - file->position)
        {
            return ACR_INFO_ERROR;
        }
        file->position += moveBy;
        return ACR_INFO_OK;
    }

    if (fromPosition == ACR_INFO_LAST && moveBy <= length)
    {
        file->position = length - moveBy;
        return ACR_INFO_OK;
    }

    return ACR_INFO_ERROR;
}

static ACR_Info_t memoryFileRead(ACR_VarBuffer_t *destination, void *userData)
{
    MemoryFile *file = static_cast<MemoryFile *>(userData);
    const ACR_Length_t length = static_cast<ACR_Length_t>(file->data.size());
    if (!destination || destination->m_MaxLength < length)
    {
        return ACR_INFO_ERROR;
    }

    std::memcpy(destination->m_Buffer.m_Pointer, file->data.constData(), length);
    destination->m_Buffer.m_Length = length;
    return ACR_INFO_OK;
}

static int callbackAdd(int value, void *userData)
{
    int *total = static_cast<int *>(userData);
    *total += value;
    return *total;
}

static std::vector<TestSuite> &testSuites()
{
    static std::vector<TestSuite> suites = {
        {
            QStringLiteral("public_alignedbuffer.h"),
            QStringLiteral("Alignment helpers and aligned buffer state"),
            {
                check(QStringLiteral("Accepts a byte-aligned reference"), [] {
                    char memory[64] = {};
                    ACR_ALIGNED_BUFFER(buffer);
                    ACR_ALIGNED_BUFFER_SET_MEMORY_ALIGNED_TO(buffer, memory, sizeof(memory), 1);
                    const bool result =
                        ACR_ALIGNED_BUFFER_IS_VALID(buffer) &&
                        ACR_ALIGNED_BUFFER_GET_MEMORY(buffer) == memory &&
                        ACR_ALIGNED_BUFFER_GET_LENGTH(buffer) == sizeof(memory);
                    ACR_ALIGNED_BUFFER_FREE(buffer);
                    return result;
                }),
                check(QStringLiteral("Rounds an address up to the requested alignment"), [] {
                    char memory[64] = {};
                    ACR_ALIGNED_BUFFER(buffer);
                    ACR_ALIGNED_BUFFER_SET_MEMORY_ALIGNED_TO(buffer, memory, sizeof(memory), 16);
                    const ACR_PointerValue_t address =
                        (ACR_PointerValue_t)ACR_ALIGNED_BUFFER_GET_MEMORY(buffer);
                    const bool result =
                        ACR_ALIGNED_BUFFER_IS_VALID(buffer) &&
                        address % 16 == 0 &&
                        ACR_ALIGNED_BUFFER_GET_LENGTH(buffer) <= sizeof(memory);
                    ACR_ALIGNED_BUFFER_FREE(buffer);
                    return result;
                })
            }
        },
        {
            QStringLiteral("public_blocks.h"),
            QStringLiteral("Block sizing and byte-to-block conversion"),
            {
                check(QStringLiteral("Rounds required block counts upward"), [] {
                    return ACR_MIN_BLOCKS_NEEDED_BY_SIZE(743, 10) == 75 &&
                           ACR_MIN_BLOCKS_NEEDED_BY_SIZE(0, 10) == 0;
                }),
                check(QStringLiteral("Splits a length into full blocks and remainder"), [] {
                    ACR_Blocks_t blocks;
                    ACR_LENGTH_TO_BLOCKS_BY_SIZE(blocks, 1800, 32);
                    return blocks.m_Blocks == 56 && blocks.m_Bytes == 8;
                })
            }
        },
        {
            QStringLiteral("public_bool.h"),
            QStringLiteral("Boolean values"),
            {
                check(QStringLiteral("True and false have the expected truth values"), [] {
                    return ACR_BOOL_TRUE != ACR_BOOL_FALSE &&
                           (ACR_BOOL_TRUE != 0) &&
                           (ACR_BOOL_FALSE == 0);
                })
            }
        },
        {
            QStringLiteral("public_buffer.h"),
            QStringLiteral("Buffer validity, flags, allocation and clearing"),
            {
                check(QStringLiteral("Tracks referenced data and read-only state"), [] {
                    ACR_Byte_t memory[] = {1, 2, 3};
                    ACR_BUFFER_FROM_DATA(buffer, memory, sizeof(memory));
                    const bool valid = ACR_BUFFER_IS_VALID(buffer) &&
                                       ACR_BUFFER_GET_LENGTH(buffer) == sizeof(memory);
                    ACR_BUFFER_SET_READ_ONLY(buffer, ACR_BOOL_TRUE);
                    const bool readOnly = ACR_BUFFER_IS_READ_ONLY(buffer);
                    ACR_BUFFER_SET_READ_ONLY(buffer, ACR_BOOL_FALSE);
                    const bool writable = !ACR_BUFFER_IS_READ_ONLY(buffer);
                    ACR_BUFFER_FREE(buffer);
                    return valid && readOnly && writable;
                }),
                check(QStringLiteral("Allocates, clears and frees owned data"), [] {
#if ACR_HAS_MALLOC == ACR_BOOL_TRUE
                    ACR_BUFFER(buffer);
                    ACR_BUFFER_ALLOC(buffer, 4);
                    const bool allocated = ACR_BUFFER_IS_VALID(buffer) &&
                                          ACR_BUFFER_GET_LENGTH(buffer) == 4;
                    if (allocated)
                    {
                        std::memset(buffer.m_Pointer, 0x7f, buffer.m_Length);
                        ACR_BUFFER_CLEAR(buffer);
                    }
                    const bool cleared = allocated &&
                        static_cast<ACR_Byte_t *>(buffer.m_Pointer)[0] == ACR_EMPTY_VALUE &&
                        static_cast<ACR_Byte_t *>(buffer.m_Pointer)[3] == ACR_EMPTY_VALUE;
                    ACR_BUFFER_FREE(buffer);
                    return cleared && buffer.m_Pointer == ACR_NULL;
#else
                    return ACR_HAS_MALLOC == ACR_BOOL_FALSE;
#endif
                })
            }
        },
        {
            QStringLiteral("public_byte_order.h"),
            QStringLiteral("Byte-order conversion helpers"),
            {
                check(QStringLiteral("Converts 16-bit values in both directions"), [] {
                    const ACR_Unsigned_16bit_t value = 0x1234;
                    return ACR_BYTE_ORDER_16(ACR_BYTE_ORDER_16(value)) == value;
                }),
                check(QStringLiteral("Converts 32-bit values in both directions"), [] {
                    const ACR_Unsigned_32bit_t value = 0x12345678UL;
                    return ACR_BYTE_ORDER_32(ACR_BYTE_ORDER_32(value)) == value;
                }),
                check(QStringLiteral("Converts 64-bit values in both directions"), [] {
#if ACR_USE_64BIT == ACR_BOOL_TRUE
                    const ACR_Unsigned_64bit_t value = 0x0123456789ABCDEFULL;
                    return ACR_BYTE_ORDER_64(ACR_BYTE_ORDER_64(value)) == value;
#else
                    return true;
#endif
                })
            }
        },
        {
            QStringLiteral("public_bytes_and_flags.h"),
            QStringLiteral("Byte constants and bit-flag operations"),
            {
                check(QStringLiteral("Adds and detects selected flags"), [] {
                    ACR_Flags_t flags = ACR_NO_FLAGS;
                    ACR_ADD_FLAGS(flags, ACR_FLAG_ONE | ACR_FLAG_FOUR);
                    return ACR_FLAG(1) == ACR_FLAG_ONE &&
                           ACR_HAS_ANY_FLAGS(flags, ACR_FLAG_FOUR) &&
                           ACR_HAS_ALL_FLAGS(flags, ACR_FLAG_ONE | ACR_FLAG_FOUR) &&
                           ACR_HAS_ONLY_FLAGS(flags, ACR_FLAG_ONE | ACR_FLAG_FOUR);
                }),
                check(QStringLiteral("Removes flags without changing other bits"), [] {
                    ACR_Flags_t flags = ACR_FLAG_ONE | ACR_FLAG_FOUR;
                    ACR_REMOVE_FLAGS(flags, ACR_FLAG_ONE);
                    return ACR_HAS_FLAG(flags, ACR_FLAG_FOUR) &&
                           !ACR_HAS_FLAG(flags, ACR_FLAG_ONE) &&
                           ACR_MAX_BYTE == 255;
                })
            }
        },
        {
            QStringLiteral("public_clock.h"),
            QStringLiteral("Date and time access macros"),
            {
                check(QStringLiteral("Reads date and time fields from a date-time value"), [] {
                    ACR_DATETIME(date);
                    date.tm_year = 124;
                    date.tm_mon = ACR_MONTH_FEBRUARY;
                    date.tm_mday = 29;
                    date.tm_wday = ACR_DAY_THURSDAY;
                    date.tm_hour = 12;
                    date.tm_min = 34;
                    date.tm_sec = 56;
                    return ACR_DATETIME_HAS_DATE(date) &&
                           ACR_DATETIME_HAS_TIME(date) &&
                           ACR_DATETIME_YEAR(date) == 2024 &&
                           ACR_DATETIME_MONTH(date) == ACR_MONTH_FEBRUARY &&
                           ACR_DATETIME_DAY(date) == 29 &&
                           ACR_DATETIME_DAY_OF_WEEK(date) == ACR_DAY_THURSDAY &&
                           ACR_DATETIME_HOUR(date) == 12 &&
                           ACR_DATETIME_MIN(date) == 34 &&
                           ACR_DATETIME_SEC(date) == 56;
                })
            }
        },
        {
            QStringLiteral("public_config.h"),
            QStringLiteral("Platform, compiler and IDE configuration"),
            {
                check(QStringLiteral("Reports configured platform, compiler and IDE"), [] {
                    return ACR_HAS_PLATFORM == ACR_BOOL_TRUE &&
                           ACR_HAS_COMPILER == ACR_BOOL_TRUE &&
                           ACR_HAS_IDE == ACR_BOOL_TRUE &&
                           ACR_PLATFORM_NAME[0] != '\0' &&
                           ACR_COMPILER_NAME[0] != '\0' &&
                           ACR_IDE_NAME[0] != '\0';
                })
            }
        },
        {
            QStringLiteral("public_count.h"),
            QStringLiteral("Counters and array access helpers"),
            {
                check(QStringLiteral("Reads values and pointers from an array"), [] {
                    int values[] = {3, 5, 8};
                    *ACR_POINTER_AT(int, values, 1) = 7;
                    return ACR_VALUE_AT(int, values, 1) == 7 &&
                           ACR_MAX_COUNT > ACR_ZERO_COUNT;
                }),
                check(QStringLiteral("Advances a bounded counter and wraps at its end"), [] {
                    ACR_COUNTER(counter, 2, 3, 2);
                    ACR_Count_t current = 0;
                    ACR_Bool_t hasNext = ACR_BOOL_FALSE;
                    ACR_COUNTER_CURRENT(counter, current);
                    const bool startsAtTwo = current == 2 && ACR_COUNTER_IS_VALID(counter);
                    ACR_COUNTER_NEXT(counter, current, hasNext);
                    const bool advances = hasNext == ACR_BOOL_TRUE && current == 3;
                    ACR_COUNTER_NEXT(counter, current, hasNext);
                    return startsAtTwo && advances &&
                           hasNext == ACR_BOOL_FALSE && current == 2;
                })
            }
        },
        {
            QStringLiteral("public_dates_and_times.h"),
            QStringLiteral("Calendar and unit-of-time constants"),
            {
                check(QStringLiteral("Recognizes leap years and days per year"), [] {
                    return ACR_YEAR_IS_LEAP_YEAR(2000) &&
                           !ACR_YEAR_IS_LEAP_YEAR(1900) &&
                           ACR_DAYS_PER_YEAR(2024) == 366 &&
                           ACR_DAYS_PER_YEAR(2025) == 365;
                }),
                check(QStringLiteral("Calculates month lengths and time constants"), [] {
                    return ACR_DaysPerMonth(ACR_MONTH_FEBRUARY, ACR_BOOL_TRUE) == 29 &&
                           ACR_DaysPerMonth(ACR_MONTH_FEBRUARY, ACR_BOOL_FALSE) == 28 &&
                           ACR_SEC_PER_DAY == 86400 &&
                           ACR_TIME_FROM_NTP(ACR_SEC_FROM_1900_TO_1970) == 0;
                })
            }
        },
        {
            QStringLiteral("public_debug.h"),
            QStringLiteral("Debug logging configuration"),
            {
                check(QStringLiteral("Exposes a consistent debug flag and print macro"), [] {
                    ACR_DEBUG_PRINT(0, "ACR Qt test application debug check");
                    return (ACR_IS_DEBUG == ACR_BOOL_TRUE) ||
                           (ACR_IS_DEBUG == ACR_BOOL_FALSE);
                })
            }
        },
        {
            QStringLiteral("public_decimal.h"),
            QStringLiteral("Decimal comparison and tolerance handling"),
            {
                check(QStringLiteral("Compares equal, less and greater values"), [] {
                    return ACR_DECIMAL_COMPARE(1.0f, 1.000001f) == ACR_INFO_EQUAL &&
                           ACR_DECIMAL_COMPARE(1.0f, 2.0f) == ACR_INFO_LESS &&
                           ACR_DECIMAL_COMPARE(2.0f, 1.0f) == ACR_INFO_GREATER;
                }),
                check(QStringLiteral("Reports invalid tolerances and NaN values"), [] {
                    const float nanValue = std::numeric_limits<float>::quiet_NaN();
                    return ACR_DECIMAL_TOLERANCE_COMPARE(1.0f, 2.0f, -1.0f) == ACR_INFO_UNKNOWN &&
                           ACR_DECIMAL_TOLERANCE_COMPARE(nanValue, 2.0f, 0.1f) == ACR_INFO_UNDEFINED;
                })
            }
        },
        {
            QStringLiteral("public_file.h"),
            QStringLiteral("File callback interface and file helper functions"),
            {
                check(QStringLiteral("Measures a file interface and restores its position"), [] {
                    MemoryFile memoryFile{QByteArray("helper data"), 2};
                    ACR_FILE_INTERFACE(file);
                    file.m_User = &memoryFile;
                    file.m_Position = memoryFilePosition;
                    file.m_Seek = memoryFileSeek;
                    const ACR_Length_t length = ACR_FileGetLength(&file);
                    return length == static_cast<ACR_Length_t>(memoryFile.data.size()) &&
                           memoryFile.position == 2;
                }),
                check(QStringLiteral("Reads the complete file through its callback"), [] {
                    MemoryFile memoryFile{QByteArray("helper data"), 0};
                    ACR_FILE_INTERFACE(file);
                    file.m_User = &memoryFile;
                    file.m_Position = memoryFilePosition;
                    file.m_Seek = memoryFileSeek;
                    file.m_Read = memoryFileRead;
                    ACR_BUFFER(buffer);
                    const ACR_Info_t result = ACR_FileReadAll(&file, &buffer);
                    const bool readAll = result == ACR_INFO_OK &&
                        buffer.m_Length == static_cast<ACR_Length_t>(memoryFile.data.size()) &&
                        std::memcmp(buffer.m_Pointer, memoryFile.data.constData(), buffer.m_Length) == 0;
                    ACR_BUFFER_FREE(buffer);
                    return readAll;
                })
            }
        },
        {
            QStringLiteral("public_filesystem.h"),
            QStringLiteral("File-system read, write and length helpers"),
            {
                check(QStringLiteral("Writes, measures and reads a temporary file"), [] {
#if ACR_HAS_FILESYSTEM == ACR_BOOL_TRUE
                    QTemporaryDir temporaryDirectory;
                    if (!temporaryDirectory.isValid())
                    {
                        return false;
                    }

                    const QByteArray path = QFile::encodeName(
                        temporaryDirectory.filePath(QStringLiteral("acr_public_header_test.bin")));
                    const ACR_Byte_t contents[] = {0x41, 0x43, 0x52, 0x00, 0x7f};
                    ACR_BUFFER(source);
                    ACR_BUFFER_SET_DATA(source, contents, sizeof(contents));

                    ACR_Length_t written = 0;
                    ACR_FILESYSTEM_FILE_WRITE(path.constData(), written, source, ACR_BOOL_FALSE);
                    ACR_Length_t fileLength = 0;
                    ACR_FILESYSTEM_FILE_LENGTH(path.constData(), fileLength);

                    ACR_BUFFER(destination);
                    ACR_BUFFER_ALLOC(destination, fileLength);
                    ACR_Length_t read = 0;
                    ACR_FILESYSTEM_FILE_READ(path.constData(), read, destination, 0);
                    const bool matches = written == sizeof(contents) &&
                        fileLength == sizeof(contents) &&
                        read == sizeof(contents) &&
                        std::memcmp(destination.m_Pointer, contents, sizeof(contents)) == 0;
                    ACR_BUFFER_FREE(destination);
                    ACR_BUFFER_FREE(source);
                    return matches;
#else
                    return ACR_HAS_FILESYSTEM == ACR_BOOL_FALSE;
#endif
                })
            }
        },
        {
            QStringLiteral("public_functions.h"),
            QStringLiteral("Callback declarations and common return values"),
            {
                check(QStringLiteral("Invokes a declared callback and updates its context"), [] {
                    ACR_TYPEDEF_CALLBACK(TestCallback_t, int)(int, void *);
                    TestCallback_t callback = callbackAdd;
                    int total = 4;
                    const int result = callback(3, &total);
                    ACR_UNUSED(result);
                    return total == 7 && ACR_SUCCESS == 0 && ACR_FAILURE != ACR_SUCCESS;
                })
            }
        },
        {
            QStringLiteral("public_heap.h"),
            QStringLiteral("Heap allocation, reallocation and deletion macros"),
            {
                check(QStringLiteral("Allocates zeroed values and deletes safely"), [] {
#if ACR_HAS_MALLOC == ACR_BOOL_TRUE
                    ACR_NEW_BY_COUNT(values, int, 3);
                    const bool allocated = values &&
                        values[0] == 0 && values[1] == 0 && values[2] == 0;
                    if (allocated)
                    {
                        values[1] = 42;
                    }
                    ACR_DELETE(values);
                    return allocated && values == ACR_NULL;
#else
                    return ACR_HAS_MALLOC == ACR_BOOL_FALSE;
#endif
                })
            }
        },
        {
            QStringLiteral("public_info.h"),
            QStringLiteral("Informational values and string conversion helpers"),
            {
                check(QStringLiteral("Converts information values to and from strings"), [] {
                    ACR_Byte_t text[] = {'o', 'k', '\0'};
                    const ACR_String_t source =
                        ACR_StringFromMemory(text, sizeof(text), ACR_MAX_COUNT);
                    const ACR_String_t result = ACR_InfoToString(ACR_INFO_OK);
                    const ACR_Info_t parsed = ACR_InfoFromString(source);
                    return parsed == ACR_INFO_OK &&
                        ACR_StringCompareToMemory(
                            result, text, sizeof(text), ACR_MAX_COUNT, ACR_INFO_YES) == ACR_INFO_EQUAL;
                })
            }
        },
        {
            QStringLiteral("public_int.h"),
            QStringLiteral("Fixed-width integers and bit masks"),
            {
                check(QStringLiteral("Creates 16-bit and 32-bit masks"), [] {
                    return ACR_INT_16_MASK(5) == 0x001f &&
                           ACR_INT_16_MASK(16) == 0xffff &&
                           ACR_INT_32_MASK(9) == 0x000001ffUL;
                }),
                check(QStringLiteral("Creates a 64-bit mask when supported"), [] {
#if ACR_USE_64BIT == ACR_BOOL_TRUE
                    return ACR_INT_64_MASK(64) == 0xffffffffffffffffULL &&
                           ACR_INT_64_MASK(4) == 0x0f;
#else
                    return true;
#endif
                })
            }
        },
        {
            QStringLiteral("public_math.h"),
            QStringLiteral("Math constants, formulas and running mean"),
            {
                check(QStringLiteral("Calculates areas and circumference"), [] {
                    return ACR_AREA_RECTANGLE(3, 4) == 12 &&
                           std::fabs(ACR_AREA_CIRCLE(2) - (4 * ACR_PI)) < 0.00001 &&
                           std::fabs(ACR_CIRCUMFERENCE(2) - (4 * ACR_PI)) < 0.00001;
                }),
                check(QStringLiteral("Computes powers and running means"), [] {
                    ACR_Decimal_t mean = 0;
                    ACR_Count_t count = 0;
                    ACR_RUNNING_MEAN(mean, count, 4);
                    ACR_RUNNING_MEAN(mean, count, 8);
                    return ACR_POWER_OF_UNSIGNED_INT(2, 8) == 256 &&
                           count == 2 && std::fabs(mean - 6.0f) < 0.00001f;
                })
            }
        },
        {
            QStringLiteral("public_memory.h"),
            QStringLiteral("Memory values, masks, clear and copy helpers"),
            {
                check(QStringLiteral("Creates length masks and clears memory"), [] {
                    ACR_Byte_t bytes[] = {0x31, 0x32, 0x33, 0x34};
                    ACR_CLEAR_MEMORY(bytes, sizeof(bytes));
                    return ACR_LENGTH_MASK(0) == 0 &&
                           ACR_LENGTH_MASK(8) == 0xff &&
                           bytes[0] == ACR_EMPTY_VALUE &&
                           bytes[3] == ACR_EMPTY_VALUE &&
                           ACR_NULL == nullptr;
                }),
                check(QStringLiteral("Copies memory through the portable helper"), [] {
                    ACR_Byte_t source[] = {9, 8, 7};
                    ACR_Byte_t destination[] = {0, 0, 0};
                    ACR_MEMCPY(destination, source, sizeof(source));
                    return destination[0] == 9 &&
                           destination[1] == 8 &&
                           destination[2] == 7;
                })
            }
        },
        {
            QStringLiteral("public_string.h"),
            QStringLiteral("String helpers and UTF-8 character counting"),
            {
                check(QStringLiteral("Counts UTF-8 sequences by their leading byte"), [] {
                    return ACR_UTF8_BYTE_COUNT(0x41) == 1 &&
                           ACR_UTF8_BYTE_COUNT(0xc2) == 2 &&
                           ACR_UTF8_BYTE_COUNT(0xe2) == 3 &&
                           ACR_UTF8_BYTE_COUNT(0xf0) == 4;
                }),
                check(QStringLiteral("Reads, compares and marks a string read-only"), [] {
                    ACR_Byte_t text[] = {'c', 'a', 'f', 0xc3, 0xa9, '\0'};
                    ACR_String_t string =
                        ACR_StringFromMemory(text, sizeof(text), ACR_MAX_COUNT);
                    const bool readAndCompared = string.m_Count == 4 &&
                        ACR_StringCompareToMemory(
                            string, text, sizeof(text), ACR_MAX_COUNT, ACR_INFO_YES) == ACR_INFO_EQUAL;
                    ACR_STRING_SET_READ_ONLY(string, ACR_BOOL_TRUE);
                    const bool readOnly = ACR_STRING_IS_READ_ONLY(string);
                    ACR_BUFFER_FREE(string.m_Buffer);
                    return readAndCompared && readOnly;
                })
            }
        },
        {
            QStringLiteral("public_timer.h"),
            QStringLiteral("Timer availability and timer difference helpers"),
            {
                check(QStringLiteral("Compares timer values and reports their difference"), [] {
                    ACR_Timer_t earlier = {};
                    ACR_Timer_t later = {};
                    earlier.tv_sec = 1;
                    earlier.tv_usec = 250000;
                    later.tv_sec = 2;
                    later.tv_usec = 0;
                    ACR_Time_t difference = 0;
                    ACR_Info_t comparison = ACR_INFO_UNKNOWN;
                    ACR_TIMER_DIFF_MICRO(later, earlier, difference, comparison);
                    return comparison == ACR_INFO_GREATER && difference == 750000;
                }),
                check(QStringLiteral("Timer API handles the configured timer availability"), [] {
                    ACR_Timer_t timer = {};
                    const ACR_Bool_t started = ACR_TimerStart(&timer);
#if ACR_HAS_TIMER == ACR_BOOL_TRUE
                    return started == ACR_BOOL_TRUE && ACR_TimerElapse(&timer) >= 0;
#else
                    return started == ACR_BOOL_FALSE && ACR_TimerElapse(&timer) == 0;
#endif
                })
            }
        },
        {
            QStringLiteral("public_unique_strings.h"),
            QStringLiteral("Shared status, date and direction strings"),
            {
                check(QStringLiteral("Exposes representative shared string constants"), [] {
                    return std::strcmp(ACR_INFO_STR_OK, "ok") == 0 &&
                           std::strcmp(ACR_INFO_STR_TRUE, "true") == 0 &&
                           std::strcmp(ACR_MONTH_STR_JANUARY, "january") == 0 &&
                           std::strcmp(ACR_DAY_STR_MONDAY, "monday") == 0;
                })
            }
        },
        {
            QStringLiteral("public_units.h"),
            QStringLiteral("Temperature, measure, weight and liquid conversions"),
            {
                check(QStringLiteral("Converts temperature in both directions"), [] {
                    const double fahrenheit = ACR_TEMPERATURE_C_TO_F(20.0);
                    return std::fabs(fahrenheit - 68.0) < 0.0001 &&
                           std::fabs(ACR_TEMPERATURE_F_TO_C(fahrenheit) - 20.0) < 0.0001;
                }),
                check(QStringLiteral("Converts distance, weight and liquid measures"), [] {
                    return std::fabs(ACR_MEASURE_INCHES_TO_CM(ACR_MEASURE_CM_TO_INCHES(10.0)) - 10.0) < 0.0001 &&
                           std::fabs(ACR_WEIGHT_POUNDS_TO_KILOGRAMS(ACR_WEIGHT_KILOGRAMS_TO_POUNDS(5.0)) - 5.0) < 0.0001 &&
                           std::fabs(ACR_LIQUID_GALLONS_TO_LITERS(ACR_LIQUID_LITERS_TO_GALLONS(3.0)) - 3.0) < 0.0001;
                })
            }
        },
        {
            QStringLiteral("public_varbuffer.h"),
            QStringLiteral("Variable-buffer allocation, append and resize helpers"),
            {
                check(QStringLiteral("Appends data and grows while preserving contents"), [] {
#if ACR_HAS_MALLOC == ACR_BOOL_TRUE
                    ACR_VAR_BUFFER(buffer);
                    ACR_VAR_BUFFER_ALLOC(buffer, 4);
                    const ACR_Byte_t first[] = {1, 2};
                    ACR_VAR_BUFFER_APPEND(buffer, first, sizeof(first));
                    ACR_VAR_BUFFER_CHANGE_MAX_LENGTH(buffer, 8);
                    const ACR_Byte_t second[] = {3, 4};
                    ACR_VAR_BUFFER_APPEND(buffer, second, sizeof(second));
                    const bool preserved = ACR_VAR_BUFFER_IS_VALID(buffer) &&
                        ACR_VAR_BUFFER_GET_LENGTH(buffer) == 4 &&
                        ACR_VAR_BUFFER_GET_MAX_LENGTH(buffer) == 8 &&
                        static_cast<ACR_Byte_t *>(buffer.m_Buffer.m_Pointer)[0] == 1 &&
                        static_cast<ACR_Byte_t *>(buffer.m_Buffer.m_Pointer)[3] == 4;
                    ACR_VAR_BUFFER_FREE(buffer);
                    return preserved && !ACR_VAR_BUFFER_IS_VALID(buffer);
#else
                    return ACR_HAS_MALLOC == ACR_BOOL_FALSE;
#endif
                })
            }
        },
        {
            QStringLiteral("public_version.h"),
            QStringLiteral("Library and C language version constants"),
            {
                check(QStringLiteral("Defines a positive library version and C99 baseline"), [] {
                    return ACR_MAJOR_VERSION > 0 &&
                           ACR_C_VERSION >= ACR_C_VERSION_99 &&
                           ACR_C_VERSION_99 == 6;
                })
            }
        }
    };

    return suites;
}

}

ACR_TestQt::ACR_TestQt(QWidget *parent)
    : QWidget(parent)
    , m_testTree(new QTreeWidget(this))
    , m_output(new QTextEdit(this))
    , m_summary(new QLabel(this))
    , m_runSelected(new QPushButton(tr("Run selected header"), this))
{
    setWindowTitle(tr("ACR Public Header Test Bench"));
    resize(1050, 720);

    QLabel *intro = new QLabel(
        tr("Choose a public header to run its checks, or run the complete suite. "
           "Filesystem tests use a temporary directory."),
        this);
    intro->setWordWrap(true);

    m_testTree->setColumnCount(3);
    m_testTree->setHeaderLabels(
        QStringList() << tr("Public header") << tr("Checks") << tr("Status"));
    m_testTree->setAlternatingRowColors(true);
    m_testTree->setUniformRowHeights(true);
    m_testTree->header()->setStretchLastSection(false);
    m_testTree->header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_testTree->header()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_testTree->header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    const std::vector<TestSuite> &suites = testSuites();
    for (size_t suiteIndex = 0; suiteIndex < suites.size(); ++suiteIndex)
    {
        const TestSuite &suite = suites[suiteIndex];
        QTreeWidgetItem *headerItem = new QTreeWidgetItem(m_testTree);
        headerItem->setText(0, suite.header);
        headerItem->setText(1, suite.description);
        headerItem->setText(2, tr("Not run"));
        headerItem->setData(0, Qt::UserRole, static_cast<int>(suiteIndex));

        for (const TestCase &test : suite.checks)
        {
            QTreeWidgetItem *checkItem = new QTreeWidgetItem(headerItem);
            checkItem->setText(1, test.name);
            checkItem->setText(2, tr("Not run"));
        }
    }
    m_testTree->expandAll();
    m_testTree->setCurrentItem(m_testTree->topLevelItem(0));

    QPushButton *runAll = new QPushButton(tr("Run all headers"), this);
    QPushButton *clearLog = new QPushButton(tr("Clear log"), this);
    m_runSelected->setEnabled(true);
    m_output->setReadOnly(true);
    m_output->setPlaceholderText(tr("Test results will appear here."));
    m_output->setMinimumHeight(170);
    m_summary->setText(tr("%1 public headers ready").arg(suites.size()));

    QHBoxLayout *controls = new QHBoxLayout();
    controls->addWidget(m_runSelected);
    controls->addWidget(runAll);
    controls->addStretch(1);
    controls->addWidget(m_summary);
    controls->addWidget(clearLog);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(intro);
    layout->addLayout(controls);
    layout->addWidget(m_testTree, 3);
    layout->addWidget(m_output, 2);

    connect(m_runSelected, &QPushButton::clicked, this, [this] {
        QTreeWidgetItem *item = m_testTree->currentItem();
        while (item && item->parent())
        {
            item = item->parent();
        }
        if (item)
        {
            runSuite(item->data(0, Qt::UserRole).toInt());
        }
    });
    connect(runAll, &QPushButton::clicked, this, [this] {
        runAllSuites();
    });
    connect(clearLog, &QPushButton::clicked, m_output, &QTextEdit::clear);
}

ACR_TestQt::~ACR_TestQt()
{
}

void ACR_TestQt::runSuite(int suiteIndex)
{
    const std::vector<TestSuite> &suites = testSuites();
    if (suiteIndex < 0 || static_cast<size_t>(suiteIndex) >= suites.size())
    {
        return;
    }

    const TestSuite &suite = suites[static_cast<size_t>(suiteIndex)];
    QTreeWidgetItem *headerItem = m_testTree->topLevelItem(suiteIndex);
    int passed = 0;

    m_output->append(tr("%1  Starting %2").arg(
        QDateTime::currentDateTime().toString(QStringLiteral("HH:mm:ss")),
        suite.header));

    for (size_t checkIndex = 0; checkIndex < suite.checks.size(); ++checkIndex)
    {
        const TestCase &test = suite.checks[checkIndex];
        const bool succeeded = test.run();
        QTreeWidgetItem *checkItem = headerItem->child(static_cast<int>(checkIndex));
        checkItem->setText(2, succeeded ? tr("Passed") : tr("Failed"));
        const QColor color = succeeded ? QColor(0, 128, 0) : QColor(180, 0, 0);
        checkItem->setForeground(2, color);

        if (succeeded)
        {
            ++passed;
        }
        m_output->append(
            QStringLiteral("%1  %2 - %3")
                .arg(succeeded ? QStringLiteral("PASS") : QStringLiteral("FAIL"),
                     suite.header,
                     test.name));
        QApplication::processEvents();
    }

    const bool suitePassed = passed == static_cast<int>(suite.checks.size());
    headerItem->setText(2, tr("%1 / %2 passed")
        .arg(passed)
        .arg(suite.checks.size()));
    headerItem->setForeground(2, suitePassed ? QColor(0, 128, 0) : QColor(180, 0, 0));
    m_output->append(tr("%1  Finished %2").arg(
        QDateTime::currentDateTime().toString(QStringLiteral("HH:mm:ss")),
        suite.header));

    int completedSuites = 0;
    int successfulSuites = 0;
    for (int i = 0; i < m_testTree->topLevelItemCount(); ++i)
    {
        const QString status = m_testTree->topLevelItem(i)->text(2);
        if (status != tr("Not run"))
        {
            ++completedSuites;
            if (status.contains('/') && status.endsWith(tr("passed")))
            {
                const int suitePassedCount = status.section('/', 0, 0).trimmed().toInt();
                const int suiteCheckCount = static_cast<int>(suites[static_cast<size_t>(i)].checks.size());
                if (suitePassedCount == suiteCheckCount)
                {
                    ++successfulSuites;
                }
            }
        }
    }
    m_summary->setText(tr("%1 / %2 headers passed (%3 run)")
        .arg(successfulSuites)
        .arg(suites.size())
        .arg(completedSuites));
}

void ACR_TestQt::runAllSuites()
{
    for (size_t suiteIndex = 0; suiteIndex < testSuites().size(); ++suiteIndex)
    {
        runSuite(static_cast<int>(suiteIndex));
    }
}
