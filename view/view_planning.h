#ifndef __VIEW_PLANNING_H__
#define __VIEW_PLANNING_H__

namespace vts {

enum class EDayDisplayMode {
    ByMonthday,
    ByWeekday,
    ByYearday,
};

void        ShowPlanning();
void        ShowGanttHeader();
void        ShowMonthHeader();
void        ShowDayHeader(EDayDisplayMode mode);
std::string GetMonthName(uint32_t month);
int         GetDayCountByMonth(uint32_t month);
int         GetWeekdayByDate(uint32_t year, uint32_t month, uint32_t day);
bool        IsWeekend(uint32_t year, uint32_t month, uint32_t day);
std::string GetWeekdayName(uint32_t weekday);
bool        IsLeapYear(uint32_t year);
bool        IsLeapYear();
int         GetTotalDays();
int         GetGanttCellWidth();
}  // namespace vts

#endif
