/**
 * @file lv_conf.h
 * Configuration file for v9.5.0-dev
 */
/** zh-CN:
 * @file lv_conf.h
 * v9.5.0-dev 的配置文件
 */

/*
 * Copy this file as `lv_conf.h`
 * 1. simply next to `lvgl` folder
 * 2. or to any other place and
 *    - define `LV_CONF_INCLUDE_SIMPLE`;
 *    - add the path as an include path.
 */
/* zh-CN:
 * 将此文件复制为 `lv_conf.h`
 * 1. 放在 `lvgl` 文件夹旁边
 * 2. 或者放在任意位置，并且
 *    - 定义 `LV_CONF_INCLUDE_SIMPLE`；
 *    - 将该路径添加到包含路径中。
 */

/* clang-format off */
#if 1 /* Set this to "1" to enable content */
/* zh-CN: 将此设置为 "1" 以启用内容 */

#ifndef LV_CONF_H
#define LV_CONF_H

/* If you need to include anything here, do it inside the `__ASSEMBLY__` guard */
#if  0 && defined(__ASSEMBLY__)
#include "my_include.h"
#endif

/*====================
   COLOR SETTINGS
 *====================*/
/* zh-CN:
   颜色设置
 */

/** Color depth: 1 (I1), 8 (L8), 16 (RGB565), 24 (RGB888), 32 (XRGB8888) */
/** zh-CN: 颜色位深：1 (I1)、8 (L8)、16 (RGB565)、24 (RGB888)、32 (XRGB8888) */
#define LV_COLOR_DEPTH 16

/*=========================
   STDLIB WRAPPER SETTINGS
 *=========================*/
/* zh-CN:
   标准库包装设置
 */

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
/** zh-CN: 可选值
 * - LV_STDLIB_BUILTIN：LVGL 内置实现
 * - LV_STDLIB_CLIB：标准 C 函数，如 malloc、strlen 等
 * - LV_STDLIB_MICROPYTHON：MicroPython 实现
 * - LV_STDLIB_RTTHREAD：RT-Thread 实现
 * - LV_STDLIB_CUSTOM：在外部实现这些函数
 */
#define LV_USE_STDLIB_MALLOC    LV_STDLIB_BUILTIN

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
/** zh-CN: 可选值同上 */
#define LV_USE_STDLIB_STRING    LV_STDLIB_BUILTIN

/** Possible values
 * - LV_STDLIB_BUILTIN:     LVGL's built in implementation
 * - LV_STDLIB_CLIB:        Standard C functions, like malloc, strlen, etc
 * - LV_STDLIB_MICROPYTHON: MicroPython implementation
 * - LV_STDLIB_RTTHREAD:    RT-Thread implementation
 * - LV_STDLIB_CUSTOM:      Implement the functions externally
 */
/** zh-CN: 可选值同上 */
#define LV_USE_STDLIB_SPRINTF   LV_STDLIB_BUILTIN

#define LV_STDINT_INCLUDE       <stdint.h>
#define LV_STDDEF_INCLUDE       <stddef.h>
#define LV_STDBOOL_INCLUDE      <stdbool.h>
#define LV_INTTYPES_INCLUDE     <inttypes.h>
#define LV_LIMITS_INCLUDE       <limits.h>
#define LV_STDARG_INCLUDE       <stdarg.h>

#if LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN
    /** Size of memory available for `lv_malloc()` in bytes (>= 2kB) */
    /** zh-CN: 可用于 `lv_malloc()` 的内存大小（字节）（>= 2kB） */
    #define LV_MEM_SIZE (64 * 1024U)          /**< [bytes] */

    /** Size of the memory expand for `lv_malloc()` in bytes */
    /** zh-CN: `lv_malloc()` 的扩展内存大小（字节） */
    #define LV_MEM_POOL_EXPAND_SIZE 0

    /** Set an address for the memory pool instead of allocating it as a normal array. Can be in external SRAM too. */
    /** zh-CN: 为内存池设置一个地址，而不是将其分配为普通数组。也可以位于外部 SRAM。 */
    #define LV_MEM_ADR 0     /**< 0: unused*/
    /* Instead of an address give a memory allocator that will be called to get a memory pool for LVGL. E.g. my_malloc */
    /* zh-CN: 也可以提供一个内存分配器来为 LVGL 获取内存池，例如 my_malloc */
    #if LV_MEM_ADR == 0
        #undef LV_MEM_POOL_INCLUDE
        #undef LV_MEM_POOL_ALLOC
    #endif
#endif  /*LV_USE_STDLIB_MALLOC == LV_STDLIB_BUILTIN*/

/*====================
   HAL SETTINGS
 *====================*/
/* zh-CN:
   HAL 设置
 */

/** Default display refresh, input device read and animation step period. */
/** zh-CN: 默认的显示刷新、输入设备读取以及动画步进周期。 */
#define LV_DEF_REFR_PERIOD  33      /**< [ms] */

/** Default Dots Per Inch. Used to initialize default sizes such as widgets sized, style paddings.
 * (Not so important, you can adjust it to modify default sizes and spaces.) */
/** zh-CN: 默认 DPI。用于初始化默认大小（如部件尺寸、样式内边距）。
 * （不太关键，可通过调整影响默认尺寸与留白。） */
#define LV_DPI_DEF 130              /**< [px/inch] */

/*=================
 * OPERATING SYSTEM
 *=================*/
/** Select operating system to use. Possible options:
 * - LV_OS_NONE
 * - LV_OS_PTHREAD
 * - LV_OS_FREERTOS
 * - LV_OS_CMSIS_RTOS2
 * - LV_OS_RTTHREAD
 * - LV_OS_WINDOWS
 * - LV_OS_MQX
 * - LV_OS_SDL2
 * - LV_OS_CUSTOM */
/** zh-CN: 选择要使用的操作系统。可选项如上。 */
#define LV_USE_OS   LV_OS_NONE

#if LV_USE_OS == LV_OS_CUSTOM
    #define LV_OS_CUSTOM_INCLUDE <stdint.h>
#endif
#if LV_USE_OS == LV_OS_FREERTOS
    /*
     * Unblocking an RTOS task with a direct notification is 45% faster and uses less RAM
     * than unblocking a task using an intermediary object such as a binary semaphore.
     * RTOS task notifications can only be used when there is only one task that can be the recipient of the event.
     */
    /* zh-CN:
     * 使用直接通知解除 RTOS 任务阻塞比使用中间对象（如二值信号量）更快（约 45%）且占用更少 RAM。
     * 任务通知仅在事件接收者是唯一任务时可用。
     */
    #define LV_USE_FREERTOS_TASK_NOTIFY 1
#endif

/*========================
 * RENDERING CONFIGURATION
 *========================*/
/* zh-CN:
   渲染配置
 */

/** Align stride of all layers and images to this bytes */
/** zh-CN: 将所有图层和图像的步幅按此字节数对齐 */
#define LV_DRAW_BUF_STRIDE_ALIGN                1

/** Align start address of draw_buf addresses to this bytes*/
/** zh-CN: 将绘制缓冲区起始地址按此字节数对齐 */
#define LV_DRAW_BUF_ALIGN                       4

/** Using matrix for transformations.
 * Requirements:
 * - `LV_USE_MATRIX = 1`.
 * - Rendering engine needs to support 3x3 matrix transformations. */
/** zh-CN: 使用矩阵进行变换。
 * 要求：
 * - `LV_USE_MATRIX = 1`；
 * - 渲染引擎需支持 3x3 矩阵变换。 */
#define LV_DRAW_TRANSFORM_USE_MATRIX            0

/* If a widget has `style_opa < 255` (not `bg_opa`, `text_opa` etc) or not NORMAL blend mode
 * it is buffered into a "simple" layer before rendering. The widget can be buffered in smaller chunks.
 * "Transformed layers" (if `transform_angle/zoom` are set) use larger buffers
 * and can't be drawn in chunks. */
/* zh-CN:
 * 若部件的 `style_opa < 255`（非 `bg_opa`、`text_opa` 等）或混合模式非 NORMAL，
 * 则在渲染前会缓存在“简单”图层中。部件可按较小块进行缓冲。
 * “变换图层”（设置了 `transform_angle/zoom`）使用更大的缓冲，无法分块绘制。
 */

/** The target buffer size for simple layer chunks. */
/** zh-CN: 简单图层分块的目标缓冲大小。 */
#define LV_DRAW_LAYER_SIMPLE_BUF_SIZE    (24 * 1024)    /**< [bytes]*/

/* Limit the max allocated memory for simple and transformed layers.
 * It should be at least `LV_DRAW_LAYER_SIMPLE_BUF_SIZE` sized but if transformed layers are also used
 * it should be enough to store the largest widget too (width x height x 4 area).
 * Set it to 0 to have no limit. */
/* zh-CN:
 * 限制简单与变换图层的最大分配内存。
 * 至少应不小于 `LV_DRAW_LAYER_SIMPLE_BUF_SIZE`；若使用变换图层，
 * 还需足够存储最大部件（宽 x 高 x 4 区域）。设为 0 则不限制。
 */
#define LV_DRAW_LAYER_MAX_MEMORY 0  /**< No limit by default [bytes]*/

/** Stack size of drawing thread.
 * NOTE: If FreeType or ThorVG is enabled, it is recommended to set it to 32KB or more.
 */
/** zh-CN: 绘制线程的栈大小。
 * 注意：启用 FreeType 或 ThorVG 时，建议设置为 32KB 或更高。
 */
#define LV_DRAW_THREAD_STACK_SIZE    (8 * 1024)         /**< [bytes]*/

/** Thread priority of the drawing task.
 *  Higher values mean higher priority.
 *  Can use values from lv_thread_prio_t enum in lv_os.h: LV_THREAD_PRIO_LOWEST,
 *  LV_THREAD_PRIO_LOW, LV_THREAD_PRIO_MID, LV_THREAD_PRIO_HIGH, LV_THREAD_PRIO_HIGHEST
 *  Make sure the priority value aligns with the OS-specific priority levels.
 *  On systems with limited priority levels (e.g., FreeRTOS), a higher value can improve
 *  rendering performance but might cause other tasks to starve. */
/** zh-CN: 绘制任务的线程优先级。
 *  数值越大优先级越高。
 *  可使用 lv_os.h 中 lv_thread_prio_t 的枚举值。
 *  请确保与操作系统的优先级等级对应。
 *  在优先级等级有限的系统（如 FreeRTOS）上，提高该值可改善渲染性能，但可能使其他任务饥饿。
 */
#define LV_DRAW_THREAD_PRIO LV_THREAD_PRIO_HIGH

#define LV_USE_DRAW_SW 1
#if LV_USE_DRAW_SW == 1
    /*
     * Selectively disable color format support in order to reduce code size.
     * NOTE: some features use certain color formats internally, e.g.
     * - gradients use RGB888
     * - bitmaps with transparency may use ARGB8888
     */
    /* zh-CN:
     * 可选择性地禁用部分颜色格式以减少代码体积。
     * 注意：某些特性内部使用特定颜色格式，例如：
     * - 渐变使用 RGB888
     * - 透明位图可能使用 ARGB8888
     */
    #define LV_DRAW_SW_SUPPORT_RGB565       1
    #define LV_DRAW_SW_SUPPORT_RGB565_SWAPPED       1
    #define LV_DRAW_SW_SUPPORT_RGB565A8     1
    #define LV_DRAW_SW_SUPPORT_RGB888       1
    #define LV_DRAW_SW_SUPPORT_XRGB8888     1
    #define LV_DRAW_SW_SUPPORT_ARGB8888     1
    #define LV_DRAW_SW_SUPPORT_ARGB8888_PREMULTIPLIED 1
    #define LV_DRAW_SW_SUPPORT_L8           1
    #define LV_DRAW_SW_SUPPORT_AL88         1
    #define LV_DRAW_SW_SUPPORT_A8           1
    #define LV_DRAW_SW_SUPPORT_I1           1

    /* The threshold of the luminance to consider a pixel as
     * active in indexed color format */
    /* zh-CN: 判定索引颜色格式下某像素为“活动”的亮度阈值 */
    #define LV_DRAW_SW_I1_LUM_THRESHOLD 127

    /** Set number of draw units.
     *  - > 1 requires operating system to be enabled in `LV_USE_OS`.
     *  - > 1 means multiple threads will render the screen in parallel. */
    /** zh-CN: 设置绘制单元数量。
     *  - 值 > 1 需要在 `LV_USE_OS` 中启用操作系统；
     *  - 值 > 1 表示将使用多线程并行渲染屏幕。
     */
    #define LV_DRAW_SW_DRAW_UNIT_CNT    1

    /** Use Arm-2D to accelerate software (sw) rendering. */
    /** zh-CN: 使用 Arm-2D 加速软件渲染。 */
    #define LV_USE_DRAW_ARM2D_SYNC      0

    /** Enable native helium assembly to be compiled. */
    /** zh-CN: 允许编译本机 Helium 汇编。 */
    #define LV_USE_NATIVE_HELIUM_ASM    0

    /**
     * - 0: Use a simple renderer capable of drawing only simple rectangles with gradient, images, text, and straight lines only.
     * - 1: Use a complex renderer capable of drawing rounded corners, shadow, skew lines, and arcs too. */
    /** zh-CN:
     * - 0：使用简单渲染器，仅能绘制带渐变的矩形、图像、文本和直线；
     * - 1：使用复杂渲染器，支持圆角、阴影、斜线与圆弧等。
     */
    #define LV_DRAW_SW_COMPLEX          1

    #if LV_DRAW_SW_COMPLEX == 1
        /** Allow buffering some shadow calculation.
         *  LV_DRAW_SW_SHADOW_CACHE_SIZE is the maximum shadow size to buffer, where shadow size is
         *  `shadow_width + radius`.  Caching has LV_DRAW_SW_SHADOW_CACHE_SIZE^2 RAM cost. */
        /** zh-CN: 允许对部分阴影计算进行缓存。
         *  阴影大小为 `shadow_width + radius`，缓存的最大阴影尺寸由 LV_DRAW_SW_SHADOW_CACHE_SIZE 指定，
         *  缓存占用约为 LV_DRAW_SW_SHADOW_CACHE_SIZE^2 的 RAM。 */
        #define LV_DRAW_SW_SHADOW_CACHE_SIZE 0

        /** Set number of maximally-cached circle data.
         *  The circumference of 1/4 circle are saved for anti-aliasing.
         *  `radius * 4` bytes are used per circle (the most often used radiuses are saved).
         *  - 0: disables caching */
        /** zh-CN: 设置最大缓存的圆形数据个数。
         *  为抗锯齿保存 1/4 圆周数据。
         *  每个圆使用 `radius * 4` 字节（保存最常用的半径）。
         *  - 0：禁用缓存。
         */
        #define LV_DRAW_SW_CIRCLE_CACHE_SIZE 4
    #endif

    #define  LV_USE_DRAW_SW_ASM     LV_DRAW_SW_ASM_NONE

    #if LV_USE_DRAW_SW_ASM == LV_DRAW_SW_ASM_CUSTOM
        #define  LV_DRAW_SW_ASM_CUSTOM_INCLUDE ""
    #endif

    /** Enable drawing complex gradients in software: linear at an angle, radial or conical */
    /** zh-CN: 在软件渲染中启用复杂渐变：带角度的线性、径向或锥形渐变 */
    #define LV_USE_DRAW_SW_COMPLEX_GRADIENTS    0

#endif

/*Use TSi's aka (Think Silicon) NemaGFX */
/* zh-CN: 使用 TSi（Think Silicon）的 NemaGFX */
#define LV_USE_NEMA_GFX 0

#if LV_USE_NEMA_GFX
    /** Select which NemaGFX HAL to use. Possible options:
     * - LV_NEMA_HAL_CUSTOM
     * - LV_NEMA_HAL_STM32 */
    /** zh-CN: 选择使用的 NemaGFX HAL，可选：LV_NEMA_HAL_CUSTOM、LV_NEMA_HAL_STM32 */
    #define LV_USE_NEMA_HAL LV_NEMA_HAL_CUSTOM
    #if LV_USE_NEMA_HAL == LV_NEMA_HAL_STM32
        #define LV_NEMA_STM32_HAL_INCLUDE <stm32u5xx_hal.h>
    #endif

    /*Enable Vector Graphics Operations. Available only if NemaVG library is present*/
    /* zh-CN: 启用矢量图形操作（仅在存在 NemaVG 库时可用） */
    #define LV_USE_NEMA_VG 0
    #if LV_USE_NEMA_VG
        /*Define application's resolution used for VG related buffer allocation */
        /* zh-CN: 定义用于 VG 相关缓冲分配的应用分辨率 */
        #define LV_NEMA_GFX_MAX_RESX 800
        #define LV_NEMA_GFX_MAX_RESY 600
    #endif
#endif

/** Use NXP's PXP on iMX RTxxx platforms. */
/** zh-CN: 在 iMX RTxxx 平台上使用 NXP 的 PXP */
#define LV_USE_PXP 0

#if LV_USE_PXP
    /** Use PXP for drawing.*/
    /** zh-CN: 使用 PXP 进行绘制 */
    #define LV_USE_DRAW_PXP 1

    /** Use PXP to rotate display.*/
    /** zh-CN: 使用 PXP 旋转显示 */
    #define LV_USE_ROTATE_PXP 0

    #if LV_USE_DRAW_PXP && LV_USE_OS
        /** Use additional draw thread for PXP processing.*/
        /** zh-CN: 为 PXP 处理使用额外的绘制线程 */
        #define LV_USE_PXP_DRAW_THREAD 1
    #endif

    /** Enable PXP asserts. */
    /** zh-CN: 启用 PXP 断言 */
    #define LV_USE_PXP_ASSERT 0
#endif

/** Use NXP's G2D on MPU platforms. */
/** zh-CN: 在 MPU 平台上使用 NXP 的 G2D */
#define LV_USE_G2D 0

#if LV_USE_G2D
    /** Use G2D for drawing. **/
    /** zh-CN: 使用 G2D 进行绘制 */
    #define LV_USE_DRAW_G2D 1

    /** Use G2D to rotate display. **/
    /** zh-CN: 使用 G2D 旋转显示 */
    #define LV_USE_ROTATE_G2D 0

    /** Maximum number of buffers that can be stored for G2D draw unit.
     *  Includes the frame buffers and assets. */
    /** zh-CN: G2D 绘制单元可存储的最大缓冲数量（包括帧缓冲与资源）。 */
    #define LV_G2D_HASH_TABLE_SIZE 50

    #if LV_USE_DRAW_G2D && LV_USE_OS
        /** Use additional draw thread for G2D processing.*/
        /** zh-CN: 为 G2D 处理使用额外的绘制线程 */
        #define LV_USE_G2D_DRAW_THREAD 1
    #endif

    /** Enable G2D asserts. */
    /** zh-CN: 启用 G2D 断言 */
    #define LV_USE_G2D_ASSERT 0
#endif

/** Use Renesas Dave2D on RA  platforms. */
/** zh-CN: 在 RA 平台上使用 Renesas Dave2D */
#define LV_USE_DRAW_DAVE2D 0

/** Draw using cached SDL textures*/
/** zh-CN: 使用缓存的 SDL 纹理进行绘制 */
#define LV_USE_DRAW_SDL 0

/** Use VG-Lite GPU. */
/** zh-CN: 使用 VG-Lite GPU */
#define LV_USE_DRAW_VG_LITE 0
#if LV_USE_DRAW_VG_LITE
    /** Enable VG-Lite custom external 'gpu_init()' function */
    /** zh-CN: 启用 VG-Lite 的自定义外部 'gpu_init()' 函数 */
    #define LV_VG_LITE_USE_GPU_INIT 0

    /** Enable VG-Lite assert. */
    /** zh-CN: 启用 VG-Lite 断言 */
    #define LV_VG_LITE_USE_ASSERT 0

    /** VG-Lite flush commit trigger threshold. GPU will try to batch these many draw tasks. */
    /** zh-CN: VG-Lite 刷新提交触发阈值。GPU 会尝试批量处理此数量的绘制任务。 */
    #define LV_VG_LITE_FLUSH_MAX_COUNT 8

    /** Enable border to simulate shadow.
     *  NOTE: which usually improves performance,
     *  but does not guarantee the same rendering quality as the software. */
    /** zh-CN: 启用边框以模拟阴影。
     *  注意：通常能提升性能，但渲染质量可能不及软件实现。 */
    #define LV_VG_LITE_USE_BOX_SHADOW 1

    /** VG-Lite gradient maximum cache number.
     *  @note  The memory usage of a single gradient image is 4K bytes. */
    /** zh-CN: VG-Lite 渐变的最大缓存数量。
     *  注：单个渐变图像约占用 4KB 内存。 */
    #define LV_VG_LITE_GRAD_CACHE_CNT 32

    /** VG-Lite stroke maximum cache number. */
    /** zh-CN: VG-Lite 轮廓的最大缓存数量。 */
    #define LV_VG_LITE_STROKE_CACHE_CNT 32

    /** VG-Lite unaligned bitmap font maximum cache number. */
    /** zh-CN: VG-Lite 未对齐位图字体的最大缓存数量。 */
    #define LV_VG_LITE_BITMAP_FONT_CACHE_CNT 256

    /** Remove VLC_OP_CLOSE path instruction (Workaround for NXP) **/
    /** zh-CN: 移除 VLC_OP_CLOSE 路径指令（NXP 兼容性变通） */
    #define LV_VG_LITE_DISABLE_VLC_OP_CLOSE 0

    /** Disable linear gradient extension for some older versions of drivers. */
    /** zh-CN: 为部分旧版驱动禁用线性渐变扩展 */
    #define LV_VG_LITE_DISABLE_LINEAR_GRADIENT_EXT 0

    /** Maximum path dump print length (in points) */
    /** zh-CN: 路径转储打印的最大长度（以点计） */
    #define LV_VG_LITE_PATH_DUMP_MAX_LEN 1000

    /** Enable usage of the LVGL's built-in vg_lite driver */
    /** zh-CN: 启用 LVGL 内置的 vg_lite 驱动 */
    #define LV_USE_VG_LITE_DRIVER  0
    #if LV_USE_VG_LITE_DRIVER
        /** Used to pick the correct GPU series folder valid options are gc255, gc355 and gc555*/
        /** zh-CN: 选择正确的 GPU 系列目录，可选 gc255、gc355、gc555 */
        #define LV_VG_LITE_HAL_GPU_SERIES gc255

        /** Used to pick the correct GPU revision header it depends on the vendor */
        /** zh-CN: 选择正确的 GPU 修订版头文件，取决于厂商 */
        #define LV_VG_LITE_HAL_GPU_REVISION 0x40

        /** Base memory address of the GPU IP it depends on SoC,
         *  default value is for NXP based devices */
        /** zh-CN: GPU IP 的基址，取决于 SoC；默认值适用于基于 NXP 的设备 */
        #define LV_VG_LITE_HAL_GPU_BASE_ADDRESS 0x40240000
    #endif /*LV_USE_VG_LITE_DRIVER*/

    /** Use ThorVG (a software vector library) as VG-Lite driver to allow testing VGLite on PC
     *  Requires: LV_USE_THORVG_INTERNAL or LV_USE_THORVG_EXTERNAL */
    /** zh-CN: 使用 ThorVG（软件矢量库）作为 VG-Lite 驱动，以便在 PC 上测试 VGLite
     *  需要：LV_USE_THORVG_INTERNAL 或 LV_USE_THORVG_EXTERNAL */
    #define LV_USE_VG_LITE_THORVG   0
    #if LV_USE_VG_LITE_THORVG
        /** Enable LVGL's blend mode support */
        /** zh-CN: 启用 LVGL 的混合模式支持 */
        #define LV_VG_LITE_THORVG_LVGL_BLEND_SUPPORT 0

        /** Enable YUV color format support */
        /** zh-CN: 启用 YUV 颜色格式支持 */
        #define LV_VG_LITE_THORVG_YUV_SUPPORT 0

        /** Enable Linear gradient extension support */
        /** zh-CN: 启用线性渐变扩展支持 */
        #define LV_VG_LITE_THORVG_LINEAR_GRADIENT_EXT_SUPPORT 0

        /** Enable alignment on 16 pixels */
        /** zh-CN: 启用 16 像素对齐 */
        #define LV_VG_LITE_THORVG_16PIXELS_ALIGN 1

        /** Buffer address alignment */
        /** zh-CN: 缓冲区地址对齐 */
        #define LV_VG_LITE_THORVG_BUF_ADDR_ALIGN 64

        /** Enable multi-thread render */
        /** zh-CN: 启用多线程渲染 */
        #define LV_VG_LITE_THORVG_THREAD_RENDER 0
    #endif /*LV_USE_VG_LITE_THORVG*/
#endif

/** Accelerate blends, fills, etc. with STM32 DMA2D */
/** zh-CN: 使用 STM32 DMA2D 加速混合、填充等操作 */
#define LV_USE_DRAW_DMA2D 0
#if LV_USE_DRAW_DMA2D
    #define LV_DRAW_DMA2D_HAL_INCLUDE "stm32h7xx_hal.h"

    /* if enabled, the user is required to call `lv_draw_dma2d_transfer_complete_interrupt_handler`
     * upon receiving the DMA2D global interrupt
     */
    /* zh-CN: 若启用，收到 DMA2D 全局中断时，用户需调用 `lv_draw_dma2d_transfer_complete_interrupt_handler` */
    #define LV_USE_DRAW_DMA2D_INTERRUPT 0
#endif

/** Draw using cached OpenGLES textures. Requires LV_USE_OPENGLES */
/** zh-CN: 使用缓存的 OpenGLES 纹理进行绘制（需启用 LV_USE_OPENGLES） */
#define LV_USE_DRAW_OPENGLES 0
#if LV_USE_DRAW_OPENGLES
    #define LV_DRAW_OPENGLES_TEXTURE_CACHE_COUNT 64
#endif

/** Draw using espressif PPA accelerator */
/** zh-CN: 使用乐鑫 PPA 加速器进行绘制 */
#define LV_USE_PPA  0
#if LV_USE_PPA
    #define LV_USE_PPA_IMG 0
#endif

/* Use EVE FT81X GPU. */
/* zh-CN: 使用 EVE FT81X GPU */
#define LV_USE_DRAW_EVE 0
#if LV_USE_DRAW_EVE
    /* EVE_GEN value: 2, 3, or 4 */
    /* zh-CN: EVE_GEN 的取值：2、3 或 4 */
    #define LV_DRAW_EVE_EVE_GENERATION 4

    /* The maximum number of bytes to buffer before a single SPI transmission.
     * Set it to 0 to disable write buffering.
     */
    /* zh-CN: 单次 SPI 传输前可缓冲的最大字节数。设为 0 以禁用写缓冲。 */
    #define LV_DRAW_EVE_WRITE_BUFFER_SIZE 2048
#endif

/*=======================
 * FEATURE CONFIGURATION
 *=======================*/
/* zh-CN:
   功能配置
 */

/*-------------
 * Logging
 *-----------*/
/* zh-CN:
   日志
 */

/** Enable log module */
/** zh-CN: 启用日志模块 */
#define LV_USE_LOG 0
#if LV_USE_LOG
    /** Set value to one of the following levels of logging detail:
     *  - LV_LOG_LEVEL_TRACE    Log detailed information.
     *  - LV_LOG_LEVEL_INFO     Log important events.
     *  - LV_LOG_LEVEL_WARN     Log if something unwanted happened but didn't cause a problem.
     *  - LV_LOG_LEVEL_ERROR    Log only critical issues, when system may fail.
     *  - LV_LOG_LEVEL_USER     Log only custom log messages added by the user.
     *  - LV_LOG_LEVEL_NONE     Do not log anything. */
    /** zh-CN: 设置日志详细程度级别之一：TRACE（详细）、INFO（重要）、WARN（警告）、ERROR（错误）、USER（用户）、NONE（关闭）。 */
    #define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

    /** - 1: Print log with 'printf';
     *  - 0: User needs to register a callback with `lv_log_register_print_cb()`. */
    /** zh-CN: - 1：使用 'printf' 输出日志；- 0：用户需通过 `lv_log_register_print_cb()` 注册回调。 */
    #define LV_LOG_PRINTF 0

    /** Set callback to print logs.
     *  E.g `my_print`. The prototype should be `void my_print(lv_log_level_t level, const char * buf)`.
     *  Can be overwritten by `lv_log_register_print_cb`. */
    /** zh-CN: 设置日志输出回调，例如 `my_print`。原型应为 `void my_print(lv_log_level_t level, const char * buf)`。可被 `lv_log_register_print_cb` 覆盖。 */
    //#define LV_LOG_PRINT_CB

    /** - 1: Enable printing timestamp;
     *  - 0: Disable printing timestamp. */
    /** zh-CN: - 1：启用时间戳打印；- 0：禁用时间戳打印。 */
    #define LV_LOG_USE_TIMESTAMP 1

    /** - 1: Print file and line number of the log;
     *  - 0: Do not print file and line number of the log. */
    /** zh-CN: - 1：打印日志的文件名和行号；- 0：不打印。 */
    #define LV_LOG_USE_FILE_LINE 1

    /* Enable/disable LV_LOG_TRACE in modules that produces a huge number of logs. */
    /* zh-CN: 在日志量较大的模块中启用/禁用 LV_LOG_TRACE。 */
    #define LV_LOG_TRACE_MEM        1   /**< Enable/disable trace logs in memory operations. */
    #define LV_LOG_TRACE_TIMER      1   /**< Enable/disable trace logs in timer operations. */
    #define LV_LOG_TRACE_INDEV      1   /**< Enable/disable trace logs in input device operations. */
    #define LV_LOG_TRACE_DISP_REFR  1   /**< Enable/disable trace logs in display re-draw operations. */
    #define LV_LOG_TRACE_EVENT      1   /**< Enable/disable trace logs in event dispatch logic. */
    #define LV_LOG_TRACE_OBJ_CREATE 1   /**< Enable/disable trace logs in object creation (core `obj` creation plus every widget). */
    #define LV_LOG_TRACE_LAYOUT     1   /**< Enable/disable trace logs in flex- and grid-layout operations. */
    #define LV_LOG_TRACE_ANIM       1   /**< Enable/disable trace logs in animation logic. */
    #define LV_LOG_TRACE_CACHE      1   /**< Enable/disable trace logs in cache operations. */
#endif  /*LV_USE_LOG*/

/*-------------
 * Asserts
 *-----------*/
/* zh-CN:
   断言
 */

/* Enable assertion failures if an operation fails or invalid data is found.
 * If LV_USE_LOG is enabled, an error message will be printed on failure. */
/* zh-CN:
 * 当操作失败或发现无效数据时启用断言失败。
 * 若启用 LV_USE_LOG，则失败时会打印错误信息。
 */
#define LV_USE_ASSERT_NULL          1   /**< Check if the parameter is NULL. (Very fast, recommended) */
#define LV_USE_ASSERT_MALLOC        1   /**< Checks is the memory is successfully allocated or no. (Very fast, recommended) */
#define LV_USE_ASSERT_STYLE         0   /**< Check if the styles are properly initialized. (Very fast, recommended) */
#define LV_USE_ASSERT_MEM_INTEGRITY 0   /**< Check the integrity of `lv_mem` after critical operations. (Slow) */
#define LV_USE_ASSERT_OBJ           0   /**< Check the object's type and existence (e.g. not deleted). (Slow) */

/** Add a custom handler when assert happens e.g. to restart MCU. */
/** zh-CN: 在断言发生时添加自定义处理，例如重启 MCU。 */
#define LV_ASSERT_HANDLER_INCLUDE <stdint.h>
#define LV_ASSERT_HANDLER while(1);     /**< Halt by default */

/*-------------
 * Debug
 *-----------*/
/* zh-CN:
   调试
 */

/** 1: Draw random colored rectangles over the redrawn areas. */
/** zh-CN: 1：在重绘区域绘制随机彩色矩形 */
#define LV_USE_REFR_DEBUG 0

/** 1: Draw a red overlay for ARGB layers and a green overlay for RGB layers*/
/** zh-CN: 1：为 ARGB 图层绘制红色覆盖，为 RGB 图层绘制绿色覆盖 */
#define LV_USE_LAYER_DEBUG 0

/** 1: Adds the following behaviors for debugging:
 *  - Draw overlays with different colors for each draw_unit's tasks.
 *  - Draw index number of draw unit on white background.
 *  - For layers, draws index number of draw unit on black background. */
/** zh-CN: 1：添加以下调试行为：
 *  - 为各绘制单元的任务绘制不同颜色的覆盖；
 *  - 在白色背景上绘制绘制单元的索引；
 *  - 对图层，在黑色背景上绘制绘制单元索引。
 */
#define LV_USE_PARALLEL_DRAW_DEBUG 0

/*-------------
 * Others
 *-----------*/
/* zh-CN:
   其他
 */

#define LV_ENABLE_GLOBAL_CUSTOM 0
#if LV_ENABLE_GLOBAL_CUSTOM
    /** Header to include for custom 'lv_global' function" */
    /** zh-CN: 自定义 'lv_global' 函数需要包含的头文件 */
    #define LV_GLOBAL_CUSTOM_INCLUDE <stdint.h>
#endif

/** Default cache size in bytes.
 *  Used by image decoders such as `lv_lodepng` to keep the decoded image in memory.
 *  If size is not set to 0, the decoder will fail to decode when the cache is full.
 *  If size is 0, the cache function is not enabled and the decoded memory will be
 *  released immediately after use. */
/** zh-CN: 默认缓存大小（字节）。
 *  供图像解码器（如 `lv_lodepng`）使用以保留解码后的图像在内存中。
 *  若大小不为 0，当缓存满时解码器将解码失败。
 *  若大小为 0，缓存功能不启用，解码后的内存会在使用后立即释放。
 */
#define LV_CACHE_DEF_SIZE       0

/** Default number of image header cache entries. The cache is used to store the headers of images
 *  The main logic is like `LV_CACHE_DEF_SIZE` but for image headers. */
/** zh-CN: 图像头缓存的默认条目数量。该缓存用于存储图像的头部信息，逻辑类似 `LV_CACHE_DEF_SIZE`，但作用于图像头。 */
#define LV_IMAGE_HEADER_CACHE_DEF_CNT 0

/** Number of stops allowed per gradient. Increase this to allow more stops.
 *  This adds (sizeof(lv_color_t) + 1) bytes per additional stop. */
/** zh-CN: 每个渐变允许的停靠点数量。增大可支持更多停靠点。
 *  每增加一个停靠点将增加 (sizeof(lv_color_t) + 1) 字节。 */
#define LV_GRADIENT_MAX_STOPS   2

/** Adjust color mix functions rounding. GPUs might calculate color mix (blending) differently.
 *  - 0:   round down,
 *  - 64:  round up from x.75,
 *  - 128: round up from half,
 *  - 192: round up from x.25,
 *  - 254: round up */
/** zh-CN: 调整颜色混合函数的舍入方式。不同 GPU 的混合计算可能存在差异。
 *  - 0：向下舍入；
 *  - 64：从 x.75 起向上舍入；
 *  - 128：从 0.5 起向上舍入；
 *  - 192：从 x.25 起向上舍入；
 *  - 254：向上舍入。
 */
#define LV_COLOR_MIX_ROUND_OFS  0

/** Add 2 x 32-bit variables to each `lv_obj_t` to speed up getting style properties */
/** zh-CN: 为每个 `lv_obj_t` 增加 2 个 32 位变量以加速样式属性的获取 */
#define LV_OBJ_STYLE_CACHE      0

/** Add `id` field to `lv_obj_t` */
/** zh-CN: 在 `lv_obj_t` 中增加 `id` 字段 */
#define LV_USE_OBJ_ID           0

/**  Enable support widget names*/
/** zh-CN: 启用部件名称支持 */
#define LV_USE_OBJ_NAME         0

/** Automatically assign an ID when obj is created */
/** zh-CN: 对象创建时自动分配 ID */
#define LV_OBJ_ID_AUTO_ASSIGN   LV_USE_OBJ_ID

/** Use builtin obj ID handler functions:
* - lv_obj_assign_id:       Called when a widget is created. Use a separate counter for each widget class as an ID.
* - lv_obj_id_compare:      Compare the ID to decide if it matches with a requested value.
* - lv_obj_stringify_id:    Return string-ified identifier, e.g. "button3".
* - lv_obj_free_id:         Does nothing, as there is no memory allocation for the ID.
* When disabled these functions needs to be implemented by the user.*/
/** zh-CN: 使用内置对象 ID 处理函数：
* - lv_obj_assign_id：在部件创建时调用；为每种部件类使用独立计数器作为 ID；
* - lv_obj_id_compare：比较 ID 是否与请求值匹配；
* - lv_obj_stringify_id：返回字符串化的标识符，例如 "button3"；
* - lv_obj_free_id：不执行任何操作（ID 不涉及内存分配）。
* 若禁用，则需要由用户自行实现这些函数。
*/
#define LV_USE_OBJ_ID_BUILTIN   1

/** Use obj property set/get API. */
/** zh-CN: 使用对象属性设置/获取 API */
#define LV_USE_OBJ_PROPERTY 0

/** Enable property name support. */
/** zh-CN: 启用属性名称支持 */
#define LV_USE_OBJ_PROPERTY_NAME 1

/* Enable the multi-touch gesture recognition feature */
/* Gesture recognition requires the use of floats */
/* zh-CN: 启用多触点手势识别功能；手势识别需要使用浮点数 */
#define LV_USE_GESTURE_RECOGNITION 0

/*=====================
 *  COMPILER SETTINGS
 *====================*/
/* zh-CN:
   编译器设置
 */

/** For big endian systems set to 1 */
/** zh-CN: 对于大端系统设置为 1 */
#define LV_BIG_ENDIAN_SYSTEM 0

/** Define a custom attribute for `lv_tick_inc` function */
/** zh-CN: 为 `lv_tick_inc` 函数定义自定义属性 */
#define LV_ATTRIBUTE_TICK_INC

/** Define a custom attribute for `lv_timer_handler` function */
/** zh-CN: 为 `lv_timer_handler` 函数定义自定义属性 */
#define LV_ATTRIBUTE_TIMER_HANDLER

/** Define a custom attribute for `lv_display_flush_ready` function */
/** zh-CN: 为 `lv_display_flush_ready` 函数定义自定义属性 */
#define LV_ATTRIBUTE_FLUSH_READY

/** Align VG_LITE buffers on this number of bytes.
 *  @note  vglite_src_buf_aligned() uses this value to validate alignment of passed buffer pointers. */
/** zh-CN: 按此字节数对齐 VG_LITE 缓冲。
 *  注：vglite_src_buf_aligned() 使用此值校验传入缓冲指针的对齐。 */
#define LV_ATTRIBUTE_MEM_ALIGN_SIZE 1

/** Will be added where memory needs to be aligned (with -Os data might not be aligned to boundary by default).
 *  E.g. __attribute__((aligned(4)))*/
/** zh-CN: 在需要内存对齐的地方添加属性（使用 -Os 时数据可能默认不对齐），例如 __attribute__((aligned(4))) */
#define LV_ATTRIBUTE_MEM_ALIGN

/** Attribute to mark large constant arrays, for example for font bitmaps */
/** zh-CN: 标记大型常量数组的属性，例如字体位图 */
#define LV_ATTRIBUTE_LARGE_CONST

/** Compiler prefix for a large array declaration in RAM */
/** zh-CN: 在 RAM 中声明大型数组的编译器前缀 */
#define LV_ATTRIBUTE_LARGE_RAM_ARRAY

/** Place performance critical functions into a faster memory (e.g RAM) */
/** zh-CN: 将性能关键函数放入更快的内存（例如 RAM） */
#define LV_ATTRIBUTE_FAST_MEM

/** Export integer constant to binding. This macro is used with constants in the form of LV_<CONST> that
 *  should also appear on LVGL binding API such as MicroPython. */
/** zh-CN: 导出整数常量以供绑定。该宏用于 LV_<CONST> 形式的常量，使其也能出现在 LVGL 的绑定 API（如 MicroPython）中。 */
#define LV_EXPORT_CONST_INT(int_value) struct _silence_gcc_warning  /**< The default value just prevents GCC warning */

/** Prefix all global extern data with this */
/** zh-CN: 为所有全局 extern 数据添加此前缀 */
#define LV_ATTRIBUTE_EXTERN_DATA

/** Use `float` as `lv_value_precise_t` */
/** zh-CN: 使用 `float` 作为 `lv_value_precise_t` */
#define LV_USE_FLOAT            0

/** Enable matrix support
 *  - Requires `LV_USE_FLOAT = 1` */
/** zh-CN: 启用矩阵支持（需要 `LV_USE_FLOAT = 1`） */
#define LV_USE_MATRIX           0

/** Include `lvgl_private.h` in `lvgl.h` to access internal data and functions by default */
/** zh-CN: 在 `lvgl.h` 中默认包含 `lvgl_private.h` 以访问内部数据与函数 */
#ifndef LV_USE_PRIVATE_API
    #define LV_USE_PRIVATE_API  0
#endif

/*==================
 *   FONT USAGE
 *===================*/
/* zh-CN:
   字体使用
 */

/* Montserrat fonts with ASCII range and some symbols using bpp = 4
 * https://fonts.google.com/specimen/Montserrat */
/* zh-CN: Montserrat 字体，覆盖 ASCII 范围与部分符号，bpp = 4 */
#define LV_FONT_MONTSERRAT_8  0
#define LV_FONT_MONTSERRAT_10 0
#define LV_FONT_MONTSERRAT_12 0
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 0
#define LV_FONT_MONTSERRAT_18 0
#define LV_FONT_MONTSERRAT_20 0
#define LV_FONT_MONTSERRAT_22 0
#define LV_FONT_MONTSERRAT_24 0
#define LV_FONT_MONTSERRAT_26 0
#define LV_FONT_MONTSERRAT_28 0
#define LV_FONT_MONTSERRAT_30 0
#define LV_FONT_MONTSERRAT_32 0
#define LV_FONT_MONTSERRAT_34 0
#define LV_FONT_MONTSERRAT_36 0
#define LV_FONT_MONTSERRAT_38 0
#define LV_FONT_MONTSERRAT_40 0
#define LV_FONT_MONTSERRAT_42 0
#define LV_FONT_MONTSERRAT_44 0
#define LV_FONT_MONTSERRAT_46 0
#define LV_FONT_MONTSERRAT_48 0

/* Demonstrate special features */
/* zh-CN: 演示特殊特性 */
#define LV_FONT_MONTSERRAT_28_COMPRESSED    0  /**< bpp = 3 */
#define LV_FONT_DEJAVU_16_PERSIAN_HEBREW    0  /**< Hebrew, Arabic, Persian letters and all their forms */
#define LV_FONT_SOURCE_HAN_SANS_SC_14_CJK   0  /**< 1338 most common CJK radicals */
#define LV_FONT_SOURCE_HAN_SANS_SC_16_CJK   0  /**< 1338 most common CJK radicals */

/** Pixel perfect monospaced fonts */
/** zh-CN: 像素级对齐的等宽字体 */
#define LV_FONT_UNSCII_8  0
#define LV_FONT_UNSCII_16 0

/** Optionally declare custom fonts here.
 *
 *  You can use any of these fonts as the default font too and they will be available
 *  globally.  Example:
 *
 *  @code
 *  #define LV_FONT_CUSTOM_DECLARE   LV_FONT_DECLARE(my_font_1) LV_FONT_DECLARE(my_font_2)
 *  @endcode
 */
/** zh-CN: 可在此处声明自定义字体。
 *  你也可以将其中任意字体设为默认字体以全局使用。示例见上。
 */
#define LV_FONT_CUSTOM_DECLARE

/** Always set a default font */
/** zh-CN: 始终设置一个默认字体 */
#define LV_FONT_DEFAULT &lv_font_montserrat_14

/** Enable handling large font and/or fonts with a lot of characters.
 *  The limit depends on the font size, font face and bpp.
 *  A compiler error will be triggered if a font needs it. */
/** zh-CN: 启用对大型字体或字符数量众多字体的处理。
 *  限制取决于字体大小、字形与 bpp。
 *  若某字体需要该选项，将触发编译器错误提示。
 */
#define LV_FONT_FMT_TXT_LARGE 0

/** Enables/disables support for compressed fonts. */
/** zh-CN: 启用/禁用压缩字体支持 */
#define LV_USE_FONT_COMPRESSED 0

/** Enable drawing placeholders when glyph dsc is not found. */
/** zh-CN: 当未找到字形描述时启用占位符绘制 */
#define LV_USE_FONT_PLACEHOLDER 1

/*=================
 *  TEXT SETTINGS
 *=================*/
/* zh-CN:
   文本设置
 */

/**
 * Select a character encoding for strings.
 * Your IDE or editor should have the same character encoding.
 * - LV_TXT_ENC_UTF8
 * - LV_TXT_ENC_ASCII
 */
/** zh-CN:
 * 为字符串选择字符编码。你的 IDE/编辑器也应使用相同编码。
 */
#define LV_TXT_ENC LV_TXT_ENC_UTF8

/** While rendering text strings, break (wrap) text on these chars. */
/** zh-CN: 渲染文本时在这些字符处进行换行（断行）。 */
#define LV_TXT_BREAK_CHARS " ,.;:-_)]}"

/** If a word is at least this long, will break wherever "prettiest".
 *  To disable, set to a value <= 0. */
/** zh-CN: 若单词至少达到此长度，则在“较美观”的位置断行。设为 <= 0 以禁用。 */
#define LV_TXT_LINE_BREAK_LONG_LEN 0

/** Minimum number of characters in a long word to put on a line before a break.
 *  Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
/** zh-CN: 长单词在断行前一行至少保留的字符数。依赖 LV_TXT_LINE_BREAK_LONG_LEN。 */
#define LV_TXT_LINE_BREAK_LONG_PRE_MIN_LEN 3

/** Minimum number of characters in a long word to put on a line after a break.
 *  Depends on LV_TXT_LINE_BREAK_LONG_LEN. */
/** zh-CN: 长单词在断行后一行至少保留的字符数。依赖 LV_TXT_LINE_BREAK_LONG_LEN。 */
#define LV_TXT_LINE_BREAK_LONG_POST_MIN_LEN 3

/** Support bidirectional text. Allows mixing Left-to-Right and Right-to-Left text.
 *  The direction will be processed according to the Unicode Bidirectional Algorithm:
 *  https://www.w3.org/International/articles/inline-bidi-markup/uba-basics */
/** zh-CN: 支持双向文本，允许混合从左到右与从右到左的文本。
 *  方向处理遵循 Unicode 双向算法（链接见上）。 */
#define LV_USE_BIDI 0
#if LV_USE_BIDI
    /*Set the default direction. Supported values:
    *`LV_BASE_DIR_LTR` Left-to-Right
    *`LV_BASE_DIR_RTL` Right-to-Left
    *`LV_BASE_DIR_AUTO` detect text base direction*/
    /* zh-CN: 设置默认方向。支持 LTR、RTL 或自动检测。 */
    #define LV_BIDI_BASE_DIR_DEF LV_BASE_DIR_AUTO
#endif

/** Enable Arabic/Persian processing
 *  In these languages characters should be replaced with another form based on their position in the text */
/** zh-CN: 启用阿拉伯语/波斯语处理。此类语言字符会根据文本中的位置替换为其他形式。 */
#define LV_USE_ARABIC_PERSIAN_CHARS 0

/*The control character to use for signaling text recoloring*/
/* zh-CN: 用于指示文本重新着色的控制字符 */
#define LV_TXT_COLOR_CMD "#"

/*==================
 * WIDGETS
 *================*/
/* Documentation for widgets can be found here: https://docs.lvgl.io/master/widgets/index.html . */
/* zh-CN: 部件的文档请参阅链接。 */

/** 1: Causes these widgets to be given default values at creation time.
 *  - lv_buttonmatrix_t:  Get default maps:  {"Btn1", "Btn2", "Btn3", "\n", "Btn4", "Btn5", ""}, else map not set.
 *  - lv_checkbox_t    :  String label set to "Check box", else set to empty string.
 *  - lv_dropdown_t    :  Options set to "Option 1", "Option 2", "Option 3", else no values are set.
 *  - lv_roller_t      :  Options set to "Option 1", "Option 2", "Option 3", "Option 4", "Option 5", else no values are set.
 *  - lv_label_t       :  Text set to "Text", else empty string.
 *  - lv_arclabel_t   :  Text set to "Arced Text", else empty string.
 * */
/** zh-CN: 1：在创建时为以下部件赋默认值（如上所示）。 */
#define LV_WIDGETS_HAS_DEFAULT_VALUE  1

#define LV_USE_ANIMIMG    1

#define LV_USE_ARC        1

#define LV_USE_ARCLABEL  1

#define LV_USE_BAR        1

#define LV_USE_BUTTON        1

#define LV_USE_BUTTONMATRIX  1

#define LV_USE_CALENDAR   1
#if LV_USE_CALENDAR
    #define LV_CALENDAR_WEEK_STARTS_MONDAY 0
    #if LV_CALENDAR_WEEK_STARTS_MONDAY
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"}
    #else
        #define LV_CALENDAR_DEFAULT_DAY_NAMES {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"}
    #endif

    #define LV_CALENDAR_DEFAULT_MONTH_NAMES {"January", "February", "March",  "April", "May",  "June", "July", "August", "September", "October", "November", "December"}
    #define LV_USE_CALENDAR_HEADER_ARROW 1
    #define LV_USE_CALENDAR_HEADER_DROPDOWN 1
    #define LV_USE_CALENDAR_CHINESE 0
#endif  /*LV_USE_CALENDAR*/

#define LV_USE_CANVAS     1

#define LV_USE_CHART      1

#define LV_USE_CHECKBOX   1

#define LV_USE_DROPDOWN   1   /**< Requires: lv_label */

#define LV_USE_IMAGE      1   /**< Requires: lv_label */

#define LV_USE_IMAGEBUTTON     1

#define LV_USE_KEYBOARD   1

#define LV_USE_LABEL      1
#if LV_USE_LABEL
    #define LV_LABEL_TEXT_SELECTION 1   /**< Enable selecting text of the label */
    #define LV_LABEL_LONG_TXT_HINT 1    /**< Store some extra info in labels to speed up drawing of very long text */
    #define LV_LABEL_WAIT_CHAR_COUNT 3  /**< The count of wait chart */
#endif

#define LV_USE_LED        1

#define LV_USE_LINE       1

#define LV_USE_LIST       1

#define LV_USE_LOTTIE     0  /**< Requires: lv_canvas, thorvg */

#define LV_USE_MENU       1

#define LV_USE_MSGBOX     1

#define LV_USE_ROLLER     1   /**< Requires: lv_label */

#define LV_USE_SCALE      1

#define LV_USE_SLIDER     1   /**< Requires: lv_bar */

#define LV_USE_SPAN       1
#if LV_USE_SPAN
    /** A line of text can contain this maximum number of span descriptors. */
    /** zh-CN: 一行文本可包含的 span 描述符最大数量 */
    #define LV_SPAN_SNIPPET_STACK_SIZE 64
#endif

#define LV_USE_SPINBOX    1

#define LV_USE_SPINNER    1

#define LV_USE_SWITCH     1

#define LV_USE_TABLE      1

#define LV_USE_TABVIEW    1

#define LV_USE_TEXTAREA   1   /**< Requires: lv_label */
#if LV_USE_TEXTAREA != 0
    #define LV_TEXTAREA_DEF_PWD_SHOW_TIME 1500    /**< [ms] */
#endif

#define LV_USE_TILEVIEW   1

#define LV_USE_WIN        1

#define LV_USE_3DTEXTURE  0

/*==================
 * THEMES
 *==================*/
/* Documentation for themes can be found here: https://docs.lvgl.io/master/common-widget-features/styles/styles.html#themes . */
/* zh-CN: 主题相关文档请参阅链接。 */

/** A simple, impressive and very complete theme */
/** zh-CN: 一个简单但完整且效果出色的主题 */
#define LV_USE_THEME_DEFAULT 1
#if LV_USE_THEME_DEFAULT
    /** 0: Light mode; 1: Dark mode */
    /** zh-CN: 0：浅色模式；1：深色模式 */
    #define LV_THEME_DEFAULT_DARK 0

    /** 1: Enable grow on press */
    /** zh-CN: 1：启用按压时放大效果 */
    #define LV_THEME_DEFAULT_GROW 1

    /** Default transition time in ms. */
    /** zh-CN: 默认过渡时间（毫秒） */
    #define LV_THEME_DEFAULT_TRANSITION_TIME 80
#endif /*LV_USE_THEME_DEFAULT*/

/** A very simple theme that is a good starting point for a custom theme */
/** zh-CN: 非常简单的主题，适合作为自定义主题的起点 */
#define LV_USE_THEME_SIMPLE 1

/** A theme designed for monochrome displays */
/** zh-CN: 为单色显示设计的主题 */
#define LV_USE_THEME_MONO 1

/*==================
 * LAYOUTS
 *==================*/
/* Documentation for layouts can be found here: https://docs.lvgl.io/master/common-widget-features/layouts/index.html . */
/* zh-CN: 布局相关文档请参阅链接。 */

/** A layout similar to Flexbox in CSS. */
/** zh-CN: 类似于 CSS Flexbox 的布局 */
#define LV_USE_FLEX 1

/** A layout similar to Grid in CSS. */
/** zh-CN: 类似于 CSS Grid 的布局 */
#define LV_USE_GRID 1

/*====================
 * 3RD PARTS LIBRARIES
 *====================*/
/* Documentation for libraries can be found here: https://docs.lvgl.io/master/libs/index.html . */
/* zh-CN: 第三方库文档请参阅链接。 */

/* File system interfaces for common APIs */
/* zh-CN: 常用 API 的文件系统接口 */

/** Setting a default driver letter allows skipping the driver prefix in filepaths.
 *  Documentation about how to use the below driver-identifier letters can be found at
 *  https://docs.lvgl.io/master/main-modules/fs.html#lv-fs-identifier-letters . */
/** zh-CN: 设置默认驱动器字母可在路径中省略驱动器前缀。使用说明见链接。 */
#define LV_FS_DEFAULT_DRIVER_LETTER '\0'

/** API for fopen, fread, etc. */
/** zh-CN: 提供 fopen、fread 等的 API */
#define LV_USE_FS_STDIO 0
#if LV_USE_FS_STDIO
    #define LV_FS_STDIO_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_STDIO_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_STDIO_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for open, read, etc. */
/** zh-CN: 提供 open、read 等的 API */
#define LV_USE_FS_POSIX 0
#if LV_USE_FS_POSIX
    #define LV_FS_POSIX_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_POSIX_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_POSIX_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for CreateFile, ReadFile, etc. */
/** zh-CN: 提供 CreateFile、ReadFile 等的 API */
#define LV_USE_FS_WIN32 0
#if LV_USE_FS_WIN32
    #define LV_FS_WIN32_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_WIN32_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_WIN32_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for FATFS (needs to be added separately). Uses f_open, f_read, etc. */
/** zh-CN: FATFS 的 API（需单独添加），使用 f_open、f_read 等 */
#define LV_USE_FS_FATFS 0
#if LV_USE_FS_FATFS
    #define LV_FS_FATFS_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_FATFS_PATH ""         /**< Set the working directory. File/directory paths will be appended to it. */
    #define LV_FS_FATFS_CACHE_SIZE 0    /**< >0 to cache this number of bytes in lv_fs_read() */
#endif

/** API for memory-mapped file access. */
/** zh-CN: 内存映射文件访问的 API */
#define LV_USE_FS_MEMFS 0
#if LV_USE_FS_MEMFS
    #define LV_FS_MEMFS_LETTER '\0'     /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
#endif

/** API for LittleFs. */
/** zh-CN: LittleFs 的 API */
#define LV_USE_FS_LITTLEFS 0
#if LV_USE_FS_LITTLEFS
    #define LV_FS_LITTLEFS_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_LITTLEFS_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
#endif

/** API for Arduino LittleFs. */
/** zh-CN: Arduino LittleFs 的 API */
#define LV_USE_FS_ARDUINO_ESP_LITTLEFS 0
#if LV_USE_FS_ARDUINO_ESP_LITTLEFS
    #define LV_FS_ARDUINO_ESP_LITTLEFS_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_ARDUINO_ESP_LITTLEFS_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
#endif

/** API for Arduino Sd. */
/** zh-CN: Arduino Sd 的 API */
#define LV_USE_FS_ARDUINO_SD 0
#if LV_USE_FS_ARDUINO_SD
    #define LV_FS_ARDUINO_SD_LETTER '\0'  /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
    #define LV_FS_ARDUINO_SD_PATH ""      /**< Set the working directory. File/directory paths will be appended to it. */
#endif

/** API for UEFI */
/** zh-CN: UEFI 的 API */
#define LV_USE_FS_UEFI 0
#if LV_USE_FS_UEFI
    #define LV_FS_UEFI_LETTER '\0'      /**< Set an upper-case driver-identifier letter for this driver (e.g. 'A'). */
#endif

#define LV_USE_FS_FROGFS 0
#if LV_USE_FS_FROGFS
    #define LV_FS_FROGFS_LETTER '\0'
#endif

/** LODEPNG decoder library */
/** zh-CN: LODEPNG 解码库 */
#define LV_USE_LODEPNG 0

/** PNG decoder(libpng) library */
/** zh-CN: PNG 解码库（libpng） */
#define LV_USE_LIBPNG 0

/** BMP decoder library */
/** zh-CN: BMP 解码库 */
#define LV_USE_BMP 0

/** JPG + split JPG decoder library.
 *  Split JPG is a custom format optimized for embedded systems. */
/** zh-CN: JPG + 分割 JPG 解码库。分割 JPG 是针对嵌入式优化的自定义格式。 */
#define LV_USE_TJPGD 0

/** libjpeg-turbo decoder library.
 *  - Supports complete JPEG specifications and high-performance JPEG decoding. */
/** zh-CN: libjpeg-turbo 解码库。支持完整 JPEG 规范与高性能解码。 */
#define LV_USE_LIBJPEG_TURBO 0

/** WebP decoder library */
/** zh-CN: WebP 解码库 */
#define LV_USE_LIBWEBP 0

/** GIF decoder library */
/** zh-CN: GIF 解码库 */
#define LV_USE_GIF 0
#if LV_USE_GIF
    /** GIF decoder accelerate */
    /** zh-CN: GIF 解码加速 */
    #define LV_GIF_CACHE_DECODE_DATA 0
#endif

/** GStreamer library */
/** zh-CN: GStreamer 库 */
#define LV_USE_GSTREAMER 0

/** Decode bin images to RAM */
/** zh-CN: 将 bin 图像解码至 RAM */
#define LV_BIN_DECODER_RAM_LOAD 0

/** RLE decompress library */
/** zh-CN: RLE 解压库 */
#define LV_USE_RLE 0

/** QR code library */
/** zh-CN: 二维码库 */
#define LV_USE_QRCODE 0

/** Barcode code library */
/** zh-CN: 条形码库 */
#define LV_USE_BARCODE 0

/** FreeType library */
/** zh-CN: FreeType 库 */
#define LV_USE_FREETYPE 0
#if LV_USE_FREETYPE
    /** Let FreeType use LVGL memory and file porting */
    /** zh-CN: 让 FreeType 使用 LVGL 的内存与文件移植层 */
    #define LV_FREETYPE_USE_LVGL_PORT 0

    /** Cache count of glyphs in FreeType, i.e. number of glyphs that can be cached.
     *  The higher the value, the more memory will be used. */
    /** zh-CN: FreeType 中可缓存的字形数量。数值越高，使用的内存越多。 */
    #define LV_FREETYPE_CACHE_FT_GLYPH_CNT 256
#endif

/** Built-in TTF decoder */
/** zh-CN: 内置 TTF 解码器 */
#define LV_USE_TINY_TTF 0
#if LV_USE_TINY_TTF
    /* Enable loading TTF data from files */
    /* zh-CN: 启用从文件加载 TTF 数据 */
    #define LV_TINY_TTF_FILE_SUPPORT 0
    #define LV_TINY_TTF_CACHE_GLYPH_CNT 128
    #define LV_TINY_TTF_CACHE_KERNING_CNT 256
#endif

/** Rlottie library */
/** zh-CN: Rlottie 库 */
#define LV_USE_RLOTTIE 0

/** Requires `LV_USE_3DTEXTURE = 1` */
/** zh-CN: 需要 `LV_USE_3DTEXTURE = 1` */
#define LV_USE_GLTF  0

/** Enable Vector Graphic APIs
 *  Requires `LV_USE_MATRIX = 1`
 *  and a rendering engine supporting vector graphics, e.g.
 *  (LV_USE_DRAW_SW and LV_USE_THORVG) or LV_USE_DRAW_VG_LITE or LV_USE_NEMA_VG. */
/** zh-CN: 启用矢量图形 API。需要 `LV_USE_MATRIX = 1` 以及支持矢量图形的渲染引擎（如 LV_USE_DRAW_SW+LV_USE_THORVG，或 LV_USE_DRAW_VG_LITE，或 LV_USE_NEMA_VG）。 */
#define LV_USE_VECTOR_GRAPHIC  0

/** Enable ThorVG (vector graphics library) from the src/libs folder.
 *  Requires LV_USE_VECTOR_GRAPHIC */
/** zh-CN: 启用 src/libs 中的 ThorVG（矢量图形库）。需启用 LV_USE_VECTOR_GRAPHIC */
#define LV_USE_THORVG_INTERNAL 0

/** Enable ThorVG by assuming that its installed and linked to the project
 *  Requires LV_USE_VECTOR_GRAPHIC */
/** zh-CN: 假设 ThorVG 已安装并链接到项目以启用它。需启用 LV_USE_VECTOR_GRAPHIC */
#define LV_USE_THORVG_EXTERNAL 0

/** Use lvgl built-in LZ4 lib */
/** zh-CN: 使用 LVGL 内置的 LZ4 库 */
#define LV_USE_LZ4_INTERNAL  0

/** Use external LZ4 library */
/** zh-CN: 使用外部 LZ4 库 */
#define LV_USE_LZ4_EXTERNAL  0

/*SVG library
 *  - Requires `LV_USE_VECTOR_GRAPHIC = 1` */
/* zh-CN: SVG 库（需要 `LV_USE_VECTOR_GRAPHIC = 1`） */
#define LV_USE_SVG 0
#define LV_USE_SVG_ANIMATION 0
#define LV_USE_SVG_DEBUG 0

/** FFmpeg library for image decoding and playing videos.
 *  Supports all major image formats so do not enable other image decoder with it. */
/** zh-CN: FFmpeg 库用于图像解码和播放视频。支持主流图像格式，因此启用它时不要同时启用其他图像解码器。 */
#define LV_USE_FFMPEG 0
#if LV_USE_FFMPEG
    /** Dump input information to stderr */
    /** zh-CN: 向 stderr 输出输入信息 */
    #define LV_FFMPEG_DUMP_FORMAT 0
    /** Use lvgl file path in FFmpeg Player widget
     *  You won't be able to open URLs after enabling this feature.
     *  Note that FFmpeg image decoder will always use lvgl file system. */
    /** zh-CN: 在 FFmpeg 播放器部件中使用 LVGL 文件路径。启用后将无法打开 URL。注意 FFmpeg 图像解码器始终使用 LVGL 文件系统。 */
    #define LV_FFMPEG_PLAYER_USE_LV_FS 0
#endif

/*==================
 * OTHERS
 *==================*/
/* Documentation for several of the below items can be found here: https://docs.lvgl.io/master/auxiliary-modules/index.html . */
/* zh-CN: 以下多项的文档请参阅链接。 */

/** 1: Enable API to take snapshot for object */
/** zh-CN: 1：启用对象快照 API */
#define LV_USE_SNAPSHOT 0

/** 1: Enable system monitor component */
/** zh-CN: 1：启用系统监视组件 */
#define LV_USE_SYSMON   0
#if LV_USE_SYSMON
    /** Get the idle percentage. E.g. uint32_t my_get_idle(void); */
    /** zh-CN: 获取空闲百分比（例如 uint32_t my_get_idle(void);） */
    #define LV_SYSMON_GET_IDLE lv_os_get_idle_percent
    /** 1: Enable usage of lv_os_get_proc_idle_percent.*/
    /** zh-CN: 1：启用 lv_os_get_proc_idle_percent 的使用 */
    #define LV_SYSMON_PROC_IDLE_AVAILABLE 0
    #if LV_SYSMON_PROC_IDLE_AVAILABLE
        /** Get the applications idle percentage.
         * - Requires `LV_USE_OS == LV_OS_PTHREAD` */
        /** zh-CN: 获取应用的空闲百分比（需要 `LV_USE_OS == LV_OS_PTHREAD`） */
        #define LV_SYSMON_GET_PROC_IDLE lv_os_get_proc_idle_percent
    #endif

    /** 1: Show CPU usage and FPS count.
     *  - Requires `LV_USE_SYSMON = 1` */
    /** zh-CN: 1：显示 CPU 使用率与 FPS（需启用 LV_USE_SYSMON） */
    #define LV_USE_PERF_MONITOR 0
    #if LV_USE_PERF_MONITOR
        #define LV_USE_PERF_MONITOR_POS LV_ALIGN_BOTTOM_RIGHT

        /** 0: Displays performance data on the screen; 1: Prints performance data using log. */
        /** zh-CN: 0：在屏幕上显示性能数据；1：通过日志打印性能数据。 */
        #define LV_USE_PERF_MONITOR_LOG_MODE 0
    #endif

    /** 1: Show used memory and memory fragmentation.
     *     - Requires `LV_USE_STDLIB_MALLOC = LV_STDLIB_BUILTIN`
     *     - Requires `LV_USE_SYSMON = 1`*/
    /** zh-CN: 1：显示已用内存与内存碎片（需 LV_USE_STDLIB_MALLOC = LV_STDLIB_BUILTIN 且启用 LV_USE_SYSMON） */
    #define LV_USE_MEM_MONITOR 0
    #if LV_USE_MEM_MONITOR
        #define LV_USE_MEM_MONITOR_POS LV_ALIGN_BOTTOM_LEFT
    #endif
#endif /*LV_USE_SYSMON*/

/** 1: Enable runtime performance profiler */
/** zh-CN: 1：启用运行时性能分析器 */
#define LV_USE_PROFILER 0
#if LV_USE_PROFILER
    /** 1: Enable the built-in profiler */
    /** zh-CN: 1：启用内置分析器 */
    #define LV_USE_PROFILER_BUILTIN 1
    #if LV_USE_PROFILER_BUILTIN
        /** Default profiler trace buffer size */
        /** zh-CN: 默认分析器跟踪缓冲大小 */
        #define LV_PROFILER_BUILTIN_BUF_SIZE (16 * 1024)     /**< [bytes] */
        #define LV_PROFILER_BUILTIN_DEFAULT_ENABLE 1
        #define LV_USE_PROFILER_BUILTIN_POSIX 0 /**< Enable POSIX profiler port */
    #endif

    /** Header to include for profiler */
    /** zh-CN: 分析器需要包含的头文件 */
    #define LV_PROFILER_INCLUDE "lvgl/src/misc/lv_profiler_builtin.h"

    /** Profiler start point function */
    /** zh-CN: 分析器起点函数 */
    #define LV_PROFILER_BEGIN    LV_PROFILER_BUILTIN_BEGIN

    /** Profiler end point function */
    /** zh-CN: 分析器终点函数 */
    #define LV_PROFILER_END      LV_PROFILER_BUILTIN_END

    /** Profiler start point function with custom tag */
    /** zh-CN: 带自定义标签的分析器起点函数 */
    #define LV_PROFILER_BEGIN_TAG LV_PROFILER_BUILTIN_BEGIN_TAG

    /** Profiler end point function with custom tag */
    /** zh-CN: 带自定义标签的分析器终点函数 */
    #define LV_PROFILER_END_TAG   LV_PROFILER_BUILTIN_END_TAG

    /*Enable layout profiler*/
    /* zh-CN: 启用布局分析器 */
    #define LV_PROFILER_LAYOUT 1

    /*Enable disp refr profiler*/
    /* zh-CN: 启用显示刷新分析器 */
    #define LV_PROFILER_REFR 1

    /*Enable draw profiler*/
    /* zh-CN: 启用绘制分析器 */
    #define LV_PROFILER_DRAW 1

    /*Enable indev profiler*/
    /* zh-CN: 启用输入设备分析器 */
    #define LV_PROFILER_INDEV 1

    /*Enable decoder profiler*/
    /* zh-CN: 启用解码器分析器 */
    #define LV_PROFILER_DECODER 1

    /*Enable font profiler*/
    /* zh-CN: 启用字体分析器 */
    #define LV_PROFILER_FONT 1

    /*Enable fs profiler*/
    /* zh-CN: 启用文件系统分析器 */
    #define LV_PROFILER_FS 1

    /*Enable style profiler*/
    /* zh-CN: 启用样式分析器 */
    #define LV_PROFILER_STYLE 0

    /*Enable timer profiler*/
    /* zh-CN: 启用定时器分析器 */
    #define LV_PROFILER_TIMER 1

    /*Enable cache profiler*/
    /* zh-CN: 启用缓存分析器 */
    #define LV_PROFILER_CACHE 1

    /*Enable event profiler*/
    /* zh-CN: 启用事件分析器 */
    #define LV_PROFILER_EVENT 1
#endif

/** 1: Enable Monkey test */
/** zh-CN: 1：启用 Monkey 测试 */
#define LV_USE_MONKEY 0

/** 1: Enable grid navigation */
/** zh-CN: 1：启用网格导航 */
#define LV_USE_GRIDNAV 0

/** 1: Enable `lv_obj` fragment logic */
/** zh-CN: 1：启用 `lv_obj` 片段逻辑 */
#define LV_USE_FRAGMENT 0

/** 1: Support using images as font in label or span widgets */
/** zh-CN: 1：支持在 label 或 span 部件中使用图像作为字体 */
#define LV_USE_IMGFONT 0

/** 1: Enable an observer pattern implementation */
/** zh-CN: 1：启用观察者模式实现 */
#define LV_USE_OBSERVER 1

/** 1: Enable Pinyin input method
 *  - Requires: lv_keyboard */
/** zh-CN: 1：启用拼音输入法（需要 lv_keyboard） */
#define LV_USE_IME_PINYIN 0
#if LV_USE_IME_PINYIN
    /** 1: Use default thesaurus.
     *  @note  If you do not use the default thesaurus, be sure to use `lv_ime_pinyin` after setting the thesaurus. */
    /** zh-CN: 1：使用默认词库。注：若不使用默认词库，请在设置词库后再使用 `lv_ime_pinyin`。 */
    #define LV_IME_PINYIN_USE_DEFAULT_DICT 1
    /** Set maximum number of candidate panels that can be displayed.
     *  @note  This needs to be adjusted according to size of screen. */
    /** zh-CN: 设置可显示的候选面板数量上限。需根据屏幕大小调整。 */
    #define LV_IME_PINYIN_CAND_TEXT_NUM 6

    /** Use 9-key input (k9). */
    /** zh-CN: 使用九宫格输入（k9）。 */
    #define LV_IME_PINYIN_USE_K9_MODE      1
    #if LV_IME_PINYIN_USE_K9_MODE == 1
        #define LV_IME_PINYIN_K9_CAND_TEXT_NUM 3
    #endif /*LV_IME_PINYIN_USE_K9_MODE*/
#endif

/** 1: Enable file explorer.
 *  - Requires: lv_table */
/** zh-CN: 1：启用文件资源管理器（需要 lv_table） */
#define LV_USE_FILE_EXPLORER                     0
#if LV_USE_FILE_EXPLORER
    /** Maximum length of path */
    /** zh-CN: 路径的最大长度 */
    #define LV_FILE_EXPLORER_PATH_MAX_LEN        (128)
    /** Quick access bar, 1:use, 0:do not use.
     *  - Requires: lv_list */
    /** zh-CN: 快速访问栏，1：使用，0：不使用（需要 lv_list） */
    #define LV_FILE_EXPLORER_QUICK_ACCESS        1
#endif

/** 1: Enable Font manager */
/** zh-CN: 1：启用字体管理器 */
#define LV_USE_FONT_MANAGER                     0
#if LV_USE_FONT_MANAGER

/**Font manager name max length*/
/** zh-CN: 字体管理器名称的最大长度 */
#define LV_FONT_MANAGER_NAME_MAX_LEN            32

#endif

/** Enable emulated input devices, time emulation, and screenshot compares. */
/** zh-CN: 启用模拟输入设备、时间仿真与截图比对 */
#define LV_USE_TEST 0
#if LV_USE_TEST

/** Enable `lv_test_screenshot_compare`.
 * Requires lodepng and a few MB of extra RAM. */
/** zh-CN: 启用 `lv_test_screenshot_compare`（需要 lodepng 与额外数 MB 的 RAM） */
#define LV_USE_TEST_SCREENSHOT_COMPARE 0

#if LV_USE_TEST_SCREENSHOT_COMPARE
    /** 1: Automatically create missing reference images*/
    /** zh-CN: 1：自动创建缺失的参考图像 */
    #define LV_TEST_SCREENSHOT_CREATE_REFERENCE_IMAGE 1
#endif /*LV_USE_TEST_SCREENSHOT_COMPARE*/

#endif /*LV_USE_TEST*/

/** Enable loading XML UIs runtime */
/** zh-CN: 启用运行时加载 XML UI */
#define LV_USE_XML    0

/** 1: Enable text translation support */
/** zh-CN: 1：启用文本翻译支持 */
#define LV_USE_TRANSLATION 0

/*1: Enable color filter style*/
/* zh-CN: 1：启用颜色过滤样式 */
#define LV_USE_COLOR_FILTER     0

/*==================
 * DEVICES
 *==================*/
/* zh-CN:
   设备
 */

/** Use SDL to open window on PC and handle mouse and keyboard. */
/** zh-CN: 使用 SDL 在 PC 上打开窗口并处理鼠标与键盘 */
#define LV_USE_SDL              0
#if LV_USE_SDL
    #define LV_SDL_INCLUDE_PATH     <SDL2/SDL.h>
    #define LV_SDL_RENDER_MODE      LV_DISPLAY_RENDER_MODE_DIRECT   /**< LV_DISPLAY_RENDER_MODE_DIRECT is recommended for best performance */
    #define LV_SDL_BUF_COUNT        1    /**< 1 or 2 */
    #define LV_SDL_ACCELERATED      1    /**< 1: Use hardware acceleration*/
    #define LV_SDL_FULLSCREEN       0    /**< 1: Make the window full screen by default */
    #define LV_SDL_DIRECT_EXIT      1    /**< 1: Exit the application when all SDL windows are closed */
    #define LV_SDL_MOUSEWHEEL_MODE  LV_SDL_MOUSEWHEEL_MODE_ENCODER  /*LV_SDL_MOUSEWHEEL_MODE_ENCODER/CROWN*/
#endif

/** Use X11 to open window on Linux desktop and handle mouse and keyboard */
/** zh-CN: 使用 X11 在 Linux 桌面上打开窗口并处理鼠标与键盘 */
#define LV_USE_X11              0
#if LV_USE_X11
    #define LV_X11_DIRECT_EXIT         1  /**< Exit application when all X11 windows have been closed */
    #define LV_X11_DOUBLE_BUFFER       1  /**< Use double buffers for rendering */
    /* Select only 1 of the following render modes (LV_X11_RENDER_MODE_PARTIAL preferred!). */
    /* zh-CN: 仅选择以下渲染模式之一（推荐 PARTIAL）。 */
    #define LV_X11_RENDER_MODE_PARTIAL 1  /**< Partial render mode (preferred) */
    #define LV_X11_RENDER_MODE_DIRECT  0  /**< Direct render mode */
    #define LV_X11_RENDER_MODE_FULL    0  /**< Full render mode */
#endif

/** Use Wayland to open a window and handle input on Linux or BSD desktops */
/** zh-CN: 使用 Wayland 在 Linux 或 BSD 桌面上打开窗口并处理输入 */
#define LV_USE_WAYLAND          0
#if LV_USE_WAYLAND
    #define LV_WAYLAND_DIRECT_EXIT          1     /**< 1: Exit the application when all Wayland windows are closed */
#endif

/** Driver for /dev/fb */
/** zh-CN: /dev/fb 的驱动 */
#define LV_USE_LINUX_FBDEV      0
#if LV_USE_LINUX_FBDEV
    #define LV_LINUX_FBDEV_BSD           0
    #define LV_LINUX_FBDEV_RENDER_MODE   LV_DISPLAY_RENDER_MODE_PARTIAL
    #define LV_LINUX_FBDEV_BUFFER_COUNT  0
    #define LV_LINUX_FBDEV_BUFFER_SIZE   60
    #define LV_LINUX_FBDEV_MMAP          1
#endif

/** Use Nuttx to open window and handle touchscreen */
/** zh-CN: 使用 Nuttx 打开窗口并处理触摸屏 */
#define LV_USE_NUTTX    0

#if LV_USE_NUTTX
    #define LV_USE_NUTTX_INDEPENDENT_IMAGE_HEAP 0

    /** Use independent image heap for default draw buffer */
    /** zh-CN: 默认绘制缓冲使用独立的图像堆 */
    #define LV_NUTTX_DEFAULT_DRAW_BUF_USE_INDEPENDENT_IMAGE_HEAP    0

    #define LV_USE_NUTTX_LIBUV    0

    /** Use Nuttx custom init API to open window and handle touchscreen */
    /** zh-CN: 使用 Nuttx 自定义初始化 API 打开窗口并处理触摸屏 */
    #define LV_USE_NUTTX_CUSTOM_INIT    0

    /** Driver for /dev/lcd */
    /** zh-CN: /dev/lcd 驱动 */
    #define LV_USE_NUTTX_LCD      0
    #if LV_USE_NUTTX_LCD
        #define LV_NUTTX_LCD_BUFFER_COUNT    0
        #define LV_NUTTX_LCD_BUFFER_SIZE     60
    #endif

    /** Driver for /dev/input */
    /** zh-CN: /dev/input 驱动 */
    #define LV_USE_NUTTX_TOUCHSCREEN    0

    /** Touchscreen cursor size in pixels(<=0: disable cursor) */
    /** zh-CN: 触摸屏光标大小（像素）（<=0：禁用光标） */
    #define LV_NUTTX_TOUCHSCREEN_CURSOR_SIZE    0

    /** Driver for /dev/mouse */
    /** zh-CN: /dev/mouse 驱动 */
    #define LV_USE_NUTTX_MOUSE    0

    /** Mouse movement step (pixels) */
    /** zh-CN: 鼠标移动步长（像素） */
    #define LV_USE_NUTTX_MOUSE_MOVE_STEP    1

    /*NuttX trace file and its path*/
    /* zh-CN: NuttX 跟踪文件及其路径 */
    #define LV_USE_NUTTX_TRACE_FILE 0
    #if LV_USE_NUTTX_TRACE_FILE
        #define LV_NUTTX_TRACE_FILE_PATH "/data/lvgl-trace.log"
    #endif

#endif

/** Driver for /dev/dri/card */
/** zh-CN: /dev/dri/card 的驱动 */
#define LV_USE_LINUX_DRM        0

#if LV_USE_LINUX_DRM

    /* Use the MESA GBM library to allocate DMA buffers that can be
     * shared across sub-systems and libraries using the Linux DMA-BUF API.
     * The GBM library aims to provide a platform independent memory management system
     * it supports the major GPU vendors - This option requires linking with libgbm */
    /* zh-CN: 使用 MESA GBM 库分配可通过 Linux DMA-BUF API 在子系统/库间共享的 DMA 缓冲。
     * GBM 提供平台无关的内存管理系统，支持主流 GPU 厂商。启用此选项需链接 libgbm。 */
    #define LV_USE_LINUX_DRM_GBM_BUFFERS 0

    #define LV_LINUX_DRM_USE_EGL     0
#endif

/** Interface for TFT_eSPI */
/** zh-CN: TFT_eSPI 接口 */
#define LV_USE_TFT_ESPI         0

/** Interface for Lovyan_GFX */
/** zh-CN: Lovyan_GFX 接口 */
#define LV_USE_LOVYAN_GFX         0

#if LV_USE_LOVYAN_GFX
    #define LV_LGFX_USER_INCLUDE "lv_lgfx_user.hpp"

#endif /*LV_USE_LOVYAN_GFX*/

/** Driver for evdev input devices */
/** zh-CN: evdev 输入设备驱动 */
#define LV_USE_EVDEV    0

/** Driver for libinput input devices */
/** zh-CN: libinput 输入设备驱动 */
#define LV_USE_LIBINPUT    0

#if LV_USE_LIBINPUT
    #define LV_LIBINPUT_BSD    0

    /** Full keyboard support */
    /** zh-CN: 完整键盘支持 */
    #define LV_LIBINPUT_XKB             0
    #if LV_LIBINPUT_XKB
        /** "setxkbmap -query" can help find the right values for your keyboard */
        /** zh-CN: 使用 "setxkbmap -query" 可帮助找到正确的键盘配置 */
        #define LV_LIBINPUT_XKB_KEY_MAP { .rules = NULL, .model = "pc101", .layout = "us", .variant = NULL, .options = NULL }
    #endif
#endif

/* Drivers for LCD devices connected via SPI/parallel port */
/* zh-CN: 通过 SPI/并口连接的 LCD 设备驱动 */
#define LV_USE_ST7735        0
#define LV_USE_ST7789        0
#define LV_USE_ST7796        0
#define LV_USE_ILI9341       0
#define LV_USE_FT81X         0
#define LV_USE_NV3007        0

#if (LV_USE_ST7735 | LV_USE_ST7789 | LV_USE_ST7796 | LV_USE_ILI9341 | LV_USE_NV3007)
    #define LV_USE_GENERIC_MIPI 1
#else
    #define LV_USE_GENERIC_MIPI 0
#endif

/** Driver for Renesas GLCD */
/** zh-CN: Renesas GLCD 驱动 */
#define LV_USE_RENESAS_GLCDC    0

/** Driver for ST LTDC */
/** zh-CN: ST LTDC 驱动 */
#define LV_USE_ST_LTDC    0
#if LV_USE_ST_LTDC
    /* Only used for partial. */
    /* zh-CN: 仅用于局部刷新 */
    #define LV_ST_LTDC_USE_DMA2D_FLUSH 0
#endif

/** Driver for NXP ELCDIF */
/** zh-CN: NXP ELCDIF 驱动 */
#define LV_USE_NXP_ELCDIF   0

/** LVGL Windows backend */
/** zh-CN: LVGL Windows 后端 */
#define LV_USE_WINDOWS    0

/** LVGL UEFI backend */
/** zh-CN: LVGL UEFI 后端 */
#define LV_USE_UEFI 0
#if LV_USE_UEFI
    #define LV_USE_UEFI_INCLUDE "myefi.h"   /**< Header that hides the actual framework (EDK2, gnu-efi, ...) */
    #define LV_UEFI_USE_MEMORY_SERVICES 0   /**< Use the memory functions from the boot services table */
#endif

/** Use a generic OpenGL driver that can be used to embed in other applications or used with GLFW/EGL */
/** zh-CN: 使用通用 OpenGL 驱动，可嵌入其他应用或与 GLFW/EGL 搭配使用 */
#define LV_USE_OPENGLES   0
#if LV_USE_OPENGLES
    #define LV_USE_OPENGLES_DEBUG        1    /**< Enable or disable debug for opengles */
#endif

/** Use GLFW to open window on PC and handle mouse and keyboard. Requires*/
/** zh-CN: 使用 GLFW 在 PC 上打开窗口并处理鼠标与键盘 */
#define LV_USE_GLFW   0


/** QNX Screen display and input drivers */
/** zh-CN: QNX Screen 显示与输入驱动 */
#define LV_USE_QNX              0
#if LV_USE_QNX
    #define LV_QNX_BUF_COUNT        1    /**< 1 or 2 */
#endif

/*=====================
* BUILD OPTIONS
*======================*/
/* zh-CN:
  构建选项
 */

/** Enable examples to be built with the library. */
/** zh-CN: 允许随库一起构建示例 */
#define LV_BUILD_EXAMPLES 1

/** Build the demos */
/** zh-CN: 构建演示程序 */
#define LV_BUILD_DEMOS 1

/*===================
 * DEMO USAGE
 ====================*/
/* zh-CN: 演示用法 */

#if LV_BUILD_DEMOS
    /** Show some widgets. This might be required to increase `LV_MEM_SIZE`. */
    /** zh-CN: 展示一些部件。可能需要增大 `LV_MEM_SIZE`。 */
    #define LV_USE_DEMO_WIDGETS 0

    /** Demonstrate usage of encoder and keyboard. */
    /** zh-CN: 演示编码器与键盘的用法 */
    #define LV_USE_DEMO_KEYPAD_AND_ENCODER 0

    /** Benchmark your system */
    /** zh-CN: 对系统进行基准测试 */
    #define LV_USE_DEMO_BENCHMARK 0

    #if LV_USE_DEMO_BENCHMARK
        /** Use fonts where bitmaps are aligned 16 byte and has Nx16 byte stride */
        /** zh-CN: 使用位图按 16 字节对齐且步幅为 Nx16 字节的字体 */
        #define LV_DEMO_BENCHMARK_ALIGNED_FONTS 0
    #endif

    /** Render test for each primitive.
     *  - Requires at least 480x272 display. */
    /** zh-CN: 对每个图元进行渲染测试（至少需要 480x272 显示）。 */
    #define LV_USE_DEMO_RENDER 0

    /** Stress test for LVGL */
    /** zh-CN: LVGL 压力测试 */
    #define LV_USE_DEMO_STRESS 0

    /** Music player demo */
    /** zh-CN: 音乐播放器演示 */
    #define LV_USE_DEMO_MUSIC 0
    #if LV_USE_DEMO_MUSIC
        #define LV_DEMO_MUSIC_SQUARE    0
        #define LV_DEMO_MUSIC_LANDSCAPE 0
        #define LV_DEMO_MUSIC_ROUND     0
        #define LV_DEMO_MUSIC_LARGE     0
        #define LV_DEMO_MUSIC_AUTO_PLAY 0
    #endif

    /** Vector graphic demo */
    /** zh-CN: 矢量图形演示 */
    #define LV_USE_DEMO_VECTOR_GRAPHIC  0

    /** GLTF demo */
    /** zh-CN: GLTF 演示 */
    #define LV_USE_DEMO_GLTF            0

    /*---------------------------
     * Demos from lvgl/lv_demos
      ---------------------------*/

    /** Flex layout demo */
    /** zh-CN: Flex 布局演示 */
    #define LV_USE_DEMO_FLEX_LAYOUT     0

    /** Smart-phone like multi-language demo */
    /** zh-CN: 类智能手机的多语言演示 */
    #define LV_USE_DEMO_MULTILANG       0

    /*E-bike demo with Lottie animations (if LV_USE_LOTTIE is enabled)*/
    /* zh-CN: 配合 Lottie 动画的电动车演示（需启用 LV_USE_LOTTIE） */
    #define LV_USE_DEMO_EBIKE           0
    #if LV_USE_DEMO_EBIKE
        #define LV_DEMO_EBIKE_PORTRAIT  0    /*0: for 480x270..480x320, 1: for 480x800..720x1280*/
    #endif

    /** High-resolution demo */
    /** zh-CN: 高分辨率演示 */
    #define LV_USE_DEMO_HIGH_RES        0

    /* Smart watch demo */
    /* zh-CN: 智能手表演示 */
    #define LV_USE_DEMO_SMARTWATCH      0
#endif /* LV_BUILD_DEMOS */

/*--END OF LV_CONF_H--*/
/* zh-CN: LV_CONF_H 结束 */

#endif /*LV_CONF_H*/

#endif /*End of "Content enable"*/
/* zh-CN: “内容启用”的结束 */
