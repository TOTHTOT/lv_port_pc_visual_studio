/*
 * @Author: TOTHTOT 37585883+TOTHTOT@users.noreply.github.com
 * @Date: 2025-04-22 09:07:56
 * @LastEditors: TOTHTOT 37585883+TOTHTOT@users.noreply.github.com
 * @LastEditTime: 2025-04-22 17:59:05
 * @FilePath: \lv_port_pc_visual_studio\LvglWindowsSimulator\LvglWindowsSimulator.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <Windows.h>

#include <LvglWindowsIconResource.h>

#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"

// 样式
static lv_style_t style_small;
static lv_style_t style_bold;

// 常量
#define STATUS_BAR_WIDTH_PCT 15
#define STATUS_BAR_CENTER_WIDTH_PCT 70
#define WEATHER_LAYOUT_WIDTH_PCT 50

// 封装状态栏创建
static lv_obj_t* create_status_bar(lv_obj_t *up, lv_obj_t* parent, lv_obj_t* down)
{
    lv_obj_t* status_bar = lv_obj_create(parent);
    lv_obj_set_flex_flow(status_bar, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(status_bar, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(status_bar, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(status_bar, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(status_bar, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_align_to(status_bar, parent, LV_ALIGN_BOTTOM_MID, 0, 0);

    lv_obj_t* sub_cont[3];
    for (int i = 0; i < 3; i++) {
        sub_cont[i] = lv_obj_create(status_bar);
        lv_obj_set_size(sub_cont[i], LV_PCT(STATUS_BAR_WIDTH_PCT), LV_SIZE_CONTENT);
        lv_obj_set_style_bg_color(sub_cont[i], lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(sub_cont[i], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_pad_all(sub_cont[i], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(sub_cont[i], 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
    lv_obj_set_size(sub_cont[1], LV_PCT(STATUS_BAR_CENTER_WIDTH_PCT), LV_SIZE_CONTENT);

    // 电量
    lv_obj_t* vbat = lv_label_create(sub_cont[0]);
    lv_obj_add_style(vbat, &style_bold, 0);
    lv_label_set_text(vbat, LV_SYMBOL_BATTERY_3);
    lv_obj_align(vbat, LV_ALIGN_LEFT_MID, 3, 0);

    // 时间
    lv_obj_t* time = lv_label_create(sub_cont[1]);
    lv_obj_add_style(time, &style_bold, 0);
    lv_label_set_text(time, "2025-4-22(Thu)12:00");
    lv_obj_align(time, LV_ALIGN_CENTER, 0, 0);

    // 新消息
    lv_obj_t* newmessage = lv_label_create(sub_cont[2]);
    lv_obj_add_style(newmessage, &style_bold, 0);
    lv_label_set_text(newmessage, LV_SYMBOL_NEW_LINE);
    lv_obj_align(newmessage, LV_ALIGN_CENTER, -3, 0);

    return status_bar;
}

// 天气子布局
void day_weather(lv_obj_t* father)
{
    lv_obj_t* cont = lv_obj_create(father);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_size(cont, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER); // 垂直居中对齐

    // 主标签
    lv_obj_t* label = lv_label_create(cont);
    lv_obj_add_style(label, &style_small, 0);
    lv_label_set_text(label, "today");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    
    // 子布局
    lv_obj_t* sub_layout = lv_obj_create(cont);
    lv_obj_set_flex_flow(sub_layout, LV_FLEX_FLOW_ROW); // 设置为水平排列
    lv_obj_set_size(sub_layout, LV_PCT(100), LV_SIZE_CONTENT); // 宽度铺满，高度根据内容自适应
    lv_obj_set_style_pad_all(sub_layout, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(sub_layout, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(sub_layout, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(sub_layout, LV_SCROLLBAR_MODE_OFF);

    // 设置子布局内元素的对齐方式为居中
    lv_obj_set_flex_align(sub_layout, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    // 图标
    lv_obj_t* icon = lv_label_create(sub_layout);
    lv_label_set_text(icon, LV_SYMBOL_HOME);
    lv_obj_set_style_text_align(icon, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT); // 确保文本居中

    // 子子容器
    lv_obj_t* sub_sub_cont = lv_obj_create(sub_layout);
    lv_obj_set_flex_flow(sub_sub_cont, LV_FLEX_FLOW_COLUMN); // 设置为垂直排列
    lv_obj_set_size(sub_sub_cont, LV_SIZE_CONTENT, LV_SIZE_CONTENT); // 宽度和高度根据内容自适应
    lv_obj_set_style_pad_all(sub_sub_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(sub_sub_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(sub_sub_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(sub_sub_cont, LV_SCROLLBAR_MODE_OFF);

    // 子标签
    lv_obj_t* sub_label1 = lv_label_create(sub_sub_cont);
    lv_label_set_text(sub_label1, "wd: 25°C");
    lv_obj_set_style_text_align(sub_label1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT); // 确保文本居中

    lv_obj_t* sub_label2 = lv_label_create(sub_sub_cont);
    lv_label_set_text(sub_label2, "wd: 60%");
    lv_obj_set_style_text_align(sub_label2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT); // 确保文本居中
}

// 封装天气布局创建
static void create_weather_layout(lv_obj_t *up, lv_obj_t* parent, lv_obj_t* down)
{
    lv_obj_t* cont = lv_obj_create(parent);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(cont, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);
    // lv_obj_align_to(cont, up, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

    for (int i = 0; i < 2; i++) {
        lv_obj_t* weather_cont = lv_obj_create(cont);
        lv_obj_set_size(weather_cont, LV_PCT(WEATHER_LAYOUT_WIDTH_PCT), LV_SIZE_CONTENT);
        lv_obj_set_style_pad_all(weather_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(weather_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_radius(weather_cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_scrollbar_mode(weather_cont, LV_SCROLLBAR_MODE_OFF);
        day_weather(weather_cont);
    }
}

void tabview_create(lv_obj_t* parent)
{
    lv_obj_t* tabview = lv_tabview_create(parent);
    lv_obj_set_size(tabview, LV_PCT(100), LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(tabview, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(tabview, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(tabview, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(tabview, LV_SCROLLBAR_MODE_OFF);
    // 获取 TabView 的按钮容器
    lv_obj_t *tab_btns = lv_tabview_get_tab_btns(tabview);

    // 减小导航栏高度
    lv_obj_set_style_pad_ver(tab_btns, 5, LV_PART_MAIN | LV_STATE_DEFAULT);      // 设置垂直内边距为 5 像素
    lv_obj_set_style_pad_hor(tab_btns, 0, LV_PART_MAIN | LV_STATE_DEFAULT);      // 水平内边距保持为 0
    lv_obj_set_style_border_width(tab_btns, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // 去掉边框

    // 创建标签页
    lv_obj_t* tab1 = lv_tabview_add_tab(tabview, "Tab 1");
    lv_obj_t* tab2 = lv_tabview_add_tab(tabview, "Tab 2");

    create_weather_layout(NULL, tab1, NULL);
    // // 在标签页中添加内容
    // lv_obj_t* label1 = lv_label_create(tab1);
    // lv_label_set_text(label1, "This is Tab 1 content.");

    lv_obj_t* label2 = lv_label_create(tab2);
    lv_label_set_text(label2, "This is Tab 2 content.");
}
lv_obj_t *create_tabview_layout(lv_obj_t *up, lv_obj_t* parent, lv_obj_t* down)
{
    // 创建底部布局容器
    lv_obj_t* bottom_layout = lv_obj_create(parent);
    lv_obj_set_size(bottom_layout, LV_PCT(100), LV_PCT(80)); // 宽度全屏，高度自适应
    lv_obj_set_style_pad_all(bottom_layout, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // 去掉内边距
    lv_obj_set_style_border_width(bottom_layout, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // 去掉边框
    lv_obj_set_style_radius(bottom_layout, 0, LV_PART_MAIN | LV_STATE_DEFAULT); // 去掉圆角
    lv_obj_set_scrollbar_mode(bottom_layout, LV_SCROLLBAR_MODE_OFF); // 禁用滚动条
    lv_obj_align(bottom_layout, LV_ALIGN_TOP_MID, 0, 0); // 对齐到屏幕底部

    // // 在底部布局中添加内容（示例）
    // lv_obj_t* label = lv_label_create(bottom_layout);
    // lv_label_set_text(label, "This is the bottom layout.");
    // lv_obj_align(label, LV_ALIGN_CENTER, 0, 0); // 居中对齐

    tabview_create(bottom_layout);

    return bottom_layout;
}
// 主页面
void main_page(void)
{
    lv_obj_t* screen = lv_scr_act();
    
    lv_obj_t *tabview = create_tabview_layout(NULL, screen, NULL);
    lv_obj_t* status_bar = create_status_bar(NULL, screen, NULL);
    

}

int main()
{
    lv_init();

    /*
     * Optional workaround for users who wants UTF-8 console output.
     * If you don't want that behavior can comment them out.
     *
     * Suggested by jinsc123654.
     */
#if LV_TXT_ENC == LV_TXT_ENC_UTF8
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int32_t zoom_level = 100;
    bool allow_dpi_override = false;
    bool simulator_mode = true;
    lv_display_t* display = lv_windows_create_display(
        L"LVGL Windows Simulator Display 1",
        264,
        176,
        zoom_level,
        allow_dpi_override,
        simulator_mode);
    if (!display)
    {
        return -1;
    }

    HWND window_handle = lv_windows_get_display_window_handle(display);
    if (!window_handle)
    {
        return -1;
    }

    HICON icon_handle = LoadIconW(
        GetModuleHandleW(NULL),
        MAKEINTRESOURCE(IDI_LVGL_WINDOWS));
    if (icon_handle)
    {
        SendMessageW(
            window_handle,
            WM_SETICON,
            TRUE,
            (LPARAM)icon_handle);
        SendMessageW(
            window_handle,
            WM_SETICON,
            FALSE,
            (LPARAM)icon_handle);
    }

    lv_indev_t* pointer_indev = lv_windows_acquire_pointer_indev(display);
    if (!pointer_indev)
    {
        return -1;
    }

    lv_indev_t* keypad_indev = lv_windows_acquire_keypad_indev(display);
    if (!keypad_indev)
    {
        return -1;
    }

    lv_indev_t* encoder_indev = lv_windows_acquire_encoder_indev(display);
    if (!encoder_indev)
    {
        return -1;
    }

    // 初始化样式
    lv_style_init(&style_small);
    lv_style_set_text_font(&style_small, &lv_font_montserrat_10);
    lv_style_init(&style_bold);
    lv_style_set_text_font(&style_bold, &lv_font_montserrat_12);
    
    main_page();
    while (1)
    {
        uint32_t time_till_next = lv_timer_handler();
        lv_delay_ms(time_till_next);
    }

    return 0;
}
