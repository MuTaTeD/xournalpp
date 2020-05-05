/*
 * Xournal++
 *
 * Xournal widget which is the "View" widget
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <memory>

#include <gtk/gtk.h>
#include <lager/reader.hpp>
#include <util/Rectangle.h>
#include <xournalview/Viewport.h>

#include "gui/Renderer.h"

#include "gtkdrawingareascrollable.h"

class XournalWidget {
public:
    XournalWidget(std::unique_ptr<Renderer> renderer, lager::reader<Viewport> viewportReader,
                  lager::context<ViewportAction> context, lager::reader<Layout> layoutReader);

    auto getGtkWidget() -> GtkWidget*;

private:
    static auto updateScrollbar(GtkAdjustment* adj, double value, bool infinite) -> void;

    static auto initHScrolling(XournalWidget* self) -> void;
    static auto initVScrolling(XournalWidget* self) -> void;

    static auto sizeAllocateCallback(GtkWidget* widget, GdkRectangle* allocation, XournalWidget* self) -> void;
    static auto realizeCallback(GtkWidget* widget, XournalWidget* self) -> void;
    static auto drawCallback(GtkWidget* widget, cairo_t* cr, XournalWidget* self) -> gboolean;

    static auto horizontalScroll(GtkAdjustment* hadjustment, XournalWidget* self) -> void;
    static auto verticalScroll(GtkAdjustment* vadjustment, XournalWidget* self) -> void;

private:
    GtkWidget* drawingArea;

    /** Renderer */
    std::unique_ptr<Renderer> renderer;

    /** State */
    lager::reader<Viewport> viewport;
    lager::context<ViewportAction> context;
    lager::reader<Layout> layout;

    constexpr static double STEP_INCREMENT = 10;
};