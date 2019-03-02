#include <chrono>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#include "imgui/imgui.h"
#include "view_planning.h"

namespace vts {

void ShowPlanning() {
    ShowGanttHeader();
}

int GetGanttCellWidth() {
    static int width = ImGui::CalcTextSize(" xxx ").x;
    return width;
}

void ShowMonthHeader() {
    char          label[32];
    constexpr int columnCount = 12;
    int           dayLabelSize = GetGanttCellWidth();

    ImGui::Columns(columnCount, "##monthHeader", true);

    ImGuiListClipper clipper(1);

    while (clipper.Step()) {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
            for (int n = 0; n < columnCount; n++) {
                int columnWidth = GetDayCountByMonth(n + 1) * dayLabelSize;

                ImGui::SetColumnWidth(n, columnWidth);
                sprintf(label, "%s", GetMonthName(n + 1).c_str());

                ImGui::Text("%s", label);
                ImGui::NextColumn();
            }
        }
    }
}

void ShowDayHeader(EDayDisplayMode mode) {
    char   label[32] = {0};
    int    columnCount = GetTotalDays();
    int    columnWidth = GetGanttCellWidth();
    time_t rawTime;

    time(&rawTime);

    auto timeInfo = localtime(&rawTime);

    timeInfo->tm_mon = 0;
    timeInfo->tm_mday = 1;

    time_t           startTime = mktime(timeInfo);
    constexpr time_t aDay = 60l * 60l * 24l;

    ImGui::Columns(columnCount, "##dayHeader", true);

    ImGuiListClipper clipper(1);

    while (clipper.Step()) {
        for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) {
            for (int n = 0; n < columnCount; n++) {
                ImGui::SetColumnWidth(n, columnWidth);

                timeInfo = localtime(&startTime);

                switch (mode) {
                    case EDayDisplayMode::ByMonthday:
                        sprintf(label, "%d", timeInfo->tm_mday);
                        break;
                    case EDayDisplayMode::ByWeekday:
                        sprintf(label, "%s",
                                GetWeekdayName(timeInfo->tm_wday).c_str());
                        break;
                    case EDayDisplayMode::ByYearday:
                        sprintf(label, "%d", timeInfo->tm_yday + 1);
                        break;
                    default:
                        break;
                }

                if (timeInfo->tm_wday == 0 || timeInfo->tm_wday == 6)
                    ImGui::TextDisabled("%s", label);
                else
                    ImGui::Text("%s", label);

                startTime += aDay;
                ImGui::NextColumn();
            }
        }
    }
}

bool IsLeapYear() {
    auto now = std::chrono::system_clock::now();
    auto time_now = std::chrono::system_clock::to_time_t(now);
    auto timeInfo = localtime(&time_now);
    int  year = 1900 + timeInfo->tm_year;
    return IsLeapYear(year);
}

bool IsLeapYear(uint32_t year) {
    if (year % 400 == 0) {
        return true;
    }

    if (year % 4 == 0 && year % 100 != 0) {
        return true;
    }

    return false;
}

int GetTotalDays() {
    return IsLeapYear() ? 366 : 365;
}

// start with 1
std::string GetMonthName(uint32_t month) {
    std::string names[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                           "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    if (month > 12 || month < 1) {
        return "Invalid Month";
    }

    return names[month - 1];
}

// start with 1
int GetDayCountByMonth(uint32_t month) {
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (IsLeapYear()) {
        days[1] = 29;
    }

    if (month > 12 || month < 1) {
        return -1;
    }

    return days[month - 1];
}
bool IsWeekend(uint32_t year, uint32_t month, uint32_t day) {
    int weekday = GetWeekdayByDate(year, month, day);
    return weekday == 0 || weekday == 6;
}
// months start from 1 to 12
// day start from 1 to 31
// return from 0 to 6 since sunday
int GetWeekdayByDate(uint32_t year, uint32_t month, uint32_t day) {
    time_t rawTime;
    time(&rawTime);
    auto timeInfo = localtime(&rawTime);

    timeInfo->tm_year = year - 1900;
    timeInfo->tm_mon = month - 1;
    timeInfo->tm_mday = day;

    mktime(timeInfo);

    return timeInfo->tm_wday;
}
// day start from 0 since Sunday
std::string GetWeekdayName(uint32_t weekday) {
    std::string weekdays[] = {"Sun", "Mon", "Tue", "Web", "Thu", "Fri", "Sat"};

    if (weekday < 7) {
        return weekdays[weekday];
    }

    return "Invalid weekday";
}

void ShowGanttHeader() {
    int totalWidth = GetGanttCellWidth() * GetTotalDays();

    ImGui::SetNextWindowContentSize(ImVec2(totalWidth, 0.0f));
    if (ImGui::BeginChild(ImGui::GetID("PlanningChild"), ImVec2(0, 0), true,
                          ImGuiWindowFlags_HorizontalScrollbar)) {
        ShowMonthHeader();
        ShowDayHeader(EDayDisplayMode::ByMonthday);
        ShowDayHeader(EDayDisplayMode::ByWeekday);
    }
    ImGui::EndChild();
}
}  // namespace vts