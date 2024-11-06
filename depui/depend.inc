DEPS_1=source/object/alert.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/alert.h\
	include/depui/object/button.h include/depui/object/defsize.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
alert.o:: $(DEPS_1)

DEPS_2=source/debug/alloc.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h
alloc.o:: $(DEPS_2)

DEPS_3=source/object/animate.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/object/animate.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
animate.o:: $(DEPS_3)

DEPS_4=source/object/bar.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/object/bar.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
bar.o:: $(DEPS_4)

DEPS_5=source/graphics/blit.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
blit.o:: $(DEPS_5)

DEPS_6=source/graphics/blitfs.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
blitfs.o:: $(DEPS_6)

DEPS_7=source/graphics/blits.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
blits.o:: $(DEPS_7)

DEPS_8=source/graphics/blitts.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
blitts.o:: $(DEPS_8)

DEPS_9=source/object/btn.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/graphics/frame.h\
	include/depui/object/button.h include/depui/object/object.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
btn.o:: $(DEPS_9)

DEPS_10=source/object/btncanc.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/button.h include/depui/object/object.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
btncanc.o:: $(DEPS_10)

DEPS_11=source/object/btnexit.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/button.h include/depui/object/object.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
btnexit.o:: $(DEPS_11)

DEPS_12=source/object/btnok.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/button.h include/depui/object/object.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
btnok.o:: $(DEPS_12)

DEPS_13=source/object/btnpush.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/object/button.h include/depui/object/object.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
btnpush.o:: $(DEPS_13)

DEPS_14=source/object/btnradio.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/graphics/decorate.h\
	include/depui/graphics/frame.h include/depui/object/button.h\
	include/depui/object/object.h include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
btnradio.o:: $(DEPS_14)

DEPS_15=source/object/btntogg.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/object/button.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
btntogg.o:: $(DEPS_15)

DEPS_16=source/platform/buffdbl.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/clip.h\
	include/depui/graphics/decorate.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
buffdbl.o:: $(DEPS_16)

DEPS_17=source/graphics/check.c include/depui/_config.h include/depui/config.h\
	include/depui/graphics/decorate.h include/depui/types.h
check.o:: $(DEPS_17)

DEPS_18=source/object/check1.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/graphics/decorate.h\
	include/depui/graphics/frame.h include/depui/object/button.h\
	include/depui/object/object.h include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
check1.o:: $(DEPS_18)

DEPS_19=source/object/checkbox.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/graphics/decorate.h\
	include/depui/graphics/frame.h include/depui/object/button.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
checkbox.o:: $(DEPS_19)

DEPS_20=source/graphics/clip.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/macros.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
clip.o:: $(DEPS_20)

DEPS_21=source/graphics/clipblit.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/graphics/clip.h\
	include/depui/graphics/draw.h include/depui/macros.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
clipblit.o:: $(DEPS_21)

DEPS_22=source/graphics/close.c include/depui/_config.h include/depui/config.h\
	include/depui/graphics/decorate.h include/depui/types.h
close.o:: $(DEPS_22)

DEPS_23=source/object/cursor.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/cursor.h include/depui/object/defsize.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
cursor.o:: $(DEPS_23)

DEPS_24=source/graphics/decorate.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h\
	include/depui/graphics/decorate.h include/depui/macros.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
decorate.o:: $(DEPS_24)

DEPS_25=source/object/defsize.c include/depui/_config.h include/depui/config.h\
	include/depui/object/defsize.h
defsize.o:: $(DEPS_25)

DEPS_26=source/desktop/desktop.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/graphics/frame.h\
	include/depui/object/defsize.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
desktop.o:: $(DEPS_26)

DEPS_27=source/object/direct.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/direct.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
direct.o:: $(DEPS_27)

DEPS_28=source/dragdrop.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/dragdrop.h\
	include/depui/draw/draw.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
dragdrop.o:: $(DEPS_28)

DEPS_29=source/draw/draw.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/graphics/clip.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
draw.o:: $(DEPS_29)

DEPS_30=source/object/editarea.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/cursor.h include/depui/object/defsize.h\
	include/depui/object/edit.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
editarea.o:: $(DEPS_30)

DEPS_31=source/object/editline.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/cursor.h include/depui/object/defsize.h\
	include/depui/object/edit.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
editline.o:: $(DEPS_31)

DEPS_32=source/object/editor.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/button.h\
	include/depui/object/cursor.h include/depui/object/defsize.h\
	include/depui/object/edit.h include/depui/object/editor.h\
	include/depui/object/filesel.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/support/findfirs.h\
	include/depui/support/image.h include/depui/types.h
editor.o:: $(DEPS_32)

DEPS_33=source/object/editscrl.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/cursor.h\
	include/depui/object/edit.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
editscrl.o:: $(DEPS_33)

DEPS_34=source/platform/emptyin.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
emptyin.o:: $(DEPS_34)

DEPS_35=source/platform/emptyout.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
emptyout.o:: $(DEPS_35)

DEPS_36=source/event/event.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
event.o:: $(DEPS_36)

DEPS_37=source/event/event2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
event2.o:: $(DEPS_37)

DEPS_38=source/support/file1.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/support/findfirs.h
file1.o:: $(DEPS_38)

DEPS_39=source/support/file2.c include/depui/_config.h include/depui/config.h\
	include/depui/support/findfirs.h
file2.o:: $(DEPS_39)

DEPS_40=source/support/file3.c include/depui/_config.h include/depui/config.h\
	include/depui/support/findfirs.h include/depui/types.h
file3.o:: $(DEPS_40)

DEPS_41=source/support/file4.c include/depui/_config.h include/depui/config.h\
	include/depui/support/findfirs.h include/depui/types.h
file4.o:: $(DEPS_41)

DEPS_42=source/object/filesel.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/button.h\
	include/depui/object/cursor.h include/depui/object/defsize.h\
	include/depui/object/edit.h include/depui/object/filesel.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/support/findfirs.h\
	include/depui/support/image.h include/depui/types.h
filesel.o:: $(DEPS_42)

DEPS_43=source/support/findfirs.c include/depui/_config.h include/depui/config.h
findfirs.o:: $(DEPS_43)

DEPS_44=source/event/focus.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/graphics/frame.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
focus.o:: $(DEPS_44)

DEPS_45=source/support/font.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/platform/vtable.h\
	include/depui/support/font.h include/depui/types.h
font.o:: $(DEPS_45)

DEPS_46=source/support/fontaa.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/graphics/clip.h\
	include/depui/macros.h include/depui/platform/vtable.h\
	include/depui/support/font.h include/depui/types.h
fontaa.o:: $(DEPS_46)

DEPS_47=source/support/fontadd.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/platform/vtable.h\
	include/depui/support/font.h include/depui/types.h
fontadd.o:: $(DEPS_47)

DEPS_48=source/support/fontdef.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/font.h\
	include/depui/types.h
fontdef.o:: $(DEPS_48)

DEPS_49=source/support/fontdef2.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/font.h\
	include/depui/types.h
fontdef2.o:: $(DEPS_49)

DEPS_50=source/support/fontdef3.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/font.h\
	include/depui/types.h
fontdef3.o:: $(DEPS_50)

DEPS_51=source/support/fontdef4.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/font.h\
	include/depui/types.h
fontdef4.o:: $(DEPS_51)

DEPS_52=source/support/fontdef5.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/font.h\
	include/depui/types.h
fontdef5.o:: $(DEPS_52)

DEPS_53=source/support/fontdump.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/font.h\
	include/depui/types.h
fontdump.o:: $(DEPS_53)

DEPS_54=source/support/fontpix.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/graphics/clip.h\
	include/depui/macros.h include/depui/platform/vtable.h\
	include/depui/support/font.h include/depui/types.h
fontpix.o:: $(DEPS_54)

DEPS_55=source/graphics/frame.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/graphics/draw.h\
	include/depui/graphics/frame.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
frame.o:: $(DEPS_55)

DEPS_56=source/graphics/frame1.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/graphics/frame.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
frame1.o:: $(DEPS_56)

DEPS_57=source/graphics/frame2.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/graphics/frame.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
frame2.o:: $(DEPS_57)

DEPS_58=source/geometry/geom1.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/macros.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
geom1.o:: $(DEPS_58)

DEPS_59=source/geometry/geom2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/macros.h include/depui/object/defsize.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
geom2.o:: $(DEPS_59)

DEPS_60=source/geometry/geomencl.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
geomencl.o:: $(DEPS_60)

DEPS_61=source/geometry/geometry.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
geometry.o:: $(DEPS_61)

DEPS_62=source/geometry/geomjc.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
geomjc.o:: $(DEPS_62)

DEPS_63=source/geometry/geomjc2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
geomjc2.o:: $(DEPS_63)

DEPS_64=source/graphics/getpix.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
getpix.o:: $(DEPS_64)

DEPS_65=source/graphics/getpixs.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
getpixs.o:: $(DEPS_65)

DEPS_66=source/globals.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
globals.o:: $(DEPS_66)

DEPS_67=source/object/hide.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
hide.o:: $(DEPS_67)

DEPS_68=source/graphics/hline.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
hline.o:: $(DEPS_68)

DEPS_69=source/graphics/hlines.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
hlines.o:: $(DEPS_69)

DEPS_70=source/support/iblit.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
iblit.o:: $(DEPS_70)

DEPS_71=source/support/ihline.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
ihline.o:: $(DEPS_71)

DEPS_72=source/support/iload.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
iload.o:: $(DEPS_72)

DEPS_73=source/support/iload2.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
iload2.o:: $(DEPS_73)

DEPS_74=source/support/iloadbmp.c include/depui/_config.h include/depui/config.h
iloadbmp.o:: $(DEPS_74)

DEPS_75=source/support/iloadpcx.c include/depui/_config.h include/depui/config.h
iloadpcx.o:: $(DEPS_75)

DEPS_76=source/support/image.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/macros.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
image.o:: $(DEPS_76)

DEPS_77=source/support/image1.c include/depui/_config.h include/depui/config.h
image1.o:: $(DEPS_77)

DEPS_78=source/support/image16.c include/depui/_config.h include/depui/config.h
image16.o:: $(DEPS_78)

DEPS_79=source/support/image24.c include/depui/_config.h include/depui/config.h
image24.o:: $(DEPS_79)

DEPS_80=source/support/image32.c include/depui/_config.h include/depui/config.h
image32.o:: $(DEPS_80)

DEPS_81=source/support/image4.c include/depui/_config.h include/depui/config.h
image4.o:: $(DEPS_81)

DEPS_82=source/support/image8.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/platform/vtable.h\
	include/depui/support/image.h include/depui/types.h
image8.o:: $(DEPS_82)

DEPS_83=source/support/irect.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
irect.o:: $(DEPS_83)

DEPS_84=source/support/ivline.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
ivline.o:: $(DEPS_84)

DEPS_85=source/object/list.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
list.o:: $(DEPS_85)

DEPS_86=source/object/listarea.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
listarea.o:: $(DEPS_86)

DEPS_87=source/object/listdef.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/object/listdef.h\
	include/depui/types.h
listdef.o:: $(DEPS_87)

DEPS_88=source/object/menu.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/defsize.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
menu.o:: $(DEPS_88)

DEPS_89=source/object/menupd.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
menupd.o:: $(DEPS_89)

DEPS_90=source/support/mouse.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/clip.h include/depui/graphics/frame.h\
	include/depui/macros.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/support/mouse.h include/depui/types.h
mouse.o:: $(DEPS_90)

DEPS_91=source/draw/move.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/draw.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/draw.h include/depui/macros.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
move.o:: $(DEPS_91)

DEPS_92=source/object/mover.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/mover.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
mover.o:: $(DEPS_92)

DEPS_93=source/object/object.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
object.o:: $(DEPS_93)

DEPS_94=source/desktop/objexist.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
objexist.o:: $(DEPS_94)

DEPS_95=source/object/objins.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
objins.o:: $(DEPS_95)

DEPS_96=source/object/objnew.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
objnew.o:: $(DEPS_96)

DEPS_97=source/object/objrem.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
objrem.o:: $(DEPS_97)

DEPS_98=source/object/objsort.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
objsort.o:: $(DEPS_98)

DEPS_99=source/object/objzor2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
objzor2.o:: $(DEPS_99)

DEPS_100=source/object/objzord.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
objzord.o:: $(DEPS_100)

DEPS_101=source/object/panel.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/graphics/frame.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
panel.o:: $(DEPS_101)

DEPS_102=source/graphics/pixel.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
pixel.o:: $(DEPS_102)

DEPS_103=source/graphics/pixelcl.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/graphics/clip.h\
	include/depui/macros.h include/depui/types.h
pixelcl.o:: $(DEPS_103)

DEPS_104=source/graphics/pixelcl2.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/macros.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
pixelcl2.o:: $(DEPS_104)

DEPS_105=source/graphics/pixelclt.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/graphics/clip.h\
	include/depui/macros.h include/depui/types.h
pixelclt.o:: $(DEPS_105)

DEPS_106=source/graphics/pixels.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
pixels.o:: $(DEPS_106)

DEPS_107=source/graphics/pixelt.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
pixelt.o:: $(DEPS_107)

DEPS_108=source/graphics/pixelts.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
pixelts.o:: $(DEPS_108)

DEPS_109=source/platform/platform.c include/depui/_config.h include/depui/config.h
platform.o:: $(DEPS_109)

DEPS_110=source/platform/platin.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/support/mouse.h include/depui/types.h\
	source/platform/djvesa1/input.c
platin.o:: $(DEPS_110)

DEPS_111=source/platform/platout.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/graphics/clip.h\
	include/depui/graphics/decorate.h\
	include/depui/graphics/draw.h include/depui/macros.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/font.h\
	include/depui/support/image.h include/depui/support/mouse.h\
	include/depui/types.h source/platform/djvesa1/output.c
platout.o:: $(DEPS_111)

DEPS_112=source/platform/platsys.c include/depui/_config.h include/depui/config.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h source/platform/djvesa1/system.c
platsys.o:: $(DEPS_112)

DEPS_113=source/pointer/pointer.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
pointer.o:: $(DEPS_113)

DEPS_114=source/pointer/pointhld.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
pointhld.o:: $(DEPS_114)

DEPS_115=source/pointer/pointmve.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
pointmve.o:: $(DEPS_115)

DEPS_116=source/desktop/pop.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
pop.o:: $(DEPS_116)

DEPS_117=source/object/posmch.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
posmch.o:: $(DEPS_117)

DEPS_118=source/object/posmcw.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
posmcw.o:: $(DEPS_118)

DEPS_119=source/object/posmove.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/geometry/geometry.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
posmove.o:: $(DEPS_119)

DEPS_120=source/object/posmx.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
posmx.o:: $(DEPS_120)

DEPS_121=source/object/posmy.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
posmy.o:: $(DEPS_121)

DEPS_122=source/object/possize.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/geometry/geometry.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
possize.o:: $(DEPS_122)

DEPS_123=source/event/queue.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/graphics/frame.h\
	include/depui/macros.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
queue.o:: $(DEPS_123)

DEPS_124=source/graphics/radio.c include/depui/_config.h include/depui/config.h\
	include/depui/graphics/decorate.h include/depui/types.h
radio.o:: $(DEPS_124)

DEPS_125=source/object/radiogrp.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/radiogrp.h\
	include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
radiogrp.o:: $(DEPS_125)

DEPS_126=source/graphics/rect.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
rect.o:: $(DEPS_126)

DEPS_127=source/graphics/rects.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
rects.o:: $(DEPS_127)

DEPS_128=source/draw/region.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/clip.h include/depui/graphics/frame.h\
	include/depui/macros.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
region.o:: $(DEPS_128)

DEPS_129=source/draw/region2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/types.h
region2.o:: $(DEPS_129)

DEPS_130=source/draw/region3.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/types.h
region3.o:: $(DEPS_130)

DEPS_131=source/draw/region4.c include/depui/_config.h include/depui/config.h\
	include/depui/draw/region.h include/depui/macros.h\
	include/depui/types.h
region4.o:: $(DEPS_131)

DEPS_132=source/object/relation.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
relation.o:: $(DEPS_132)

DEPS_133=source/object/resize.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/geometry/geometry.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
resize.o:: $(DEPS_133)

DEPS_134=source/graphics/resize2.c include/depui/_config.h include/depui/config.h\
	include/depui/graphics/decorate.h include/depui/types.h
resize2.o:: $(DEPS_134)

DEPS_135=source/desktop/root.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/graphics/frame.h\
	include/depui/macros.h include/depui/object/list.h\
	include/depui/object/listdef.h include/depui/object/menu.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
root.o:: $(DEPS_135)

DEPS_136=source/object/scroll.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/draw.h include/depui/graphics/frame.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
scroll.o:: $(DEPS_136)

DEPS_137=source/object/scroll2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/object/object.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
scroll2.o:: $(DEPS_137)

DEPS_138=source/object/slider.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/queue.h include/depui/object/object.h\
	include/depui/object/slider.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
slider.o:: $(DEPS_138)

DEPS_139=source/object/sliderh.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/draw.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/focus.h\
	include/depui/event/queue.h include/depui/graphics/draw.h\
	include/depui/graphics/frame.h include/depui/object/defsize.h\
	include/depui/object/object.h include/depui/object/slider.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
sliderh.o:: $(DEPS_139)

DEPS_140=source/object/sliderv.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/graphics/draw.h include/depui/graphics/frame.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/object/slider.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
sliderv.o:: $(DEPS_140)

DEPS_141=source/object/statict.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/graphics/draw.h\
	include/depui/graphics/frame.h include/depui/object/defsize.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
statict.o:: $(DEPS_141)

DEPS_142=source/object/statict2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/object/object.h include/depui/object/statict.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
statict2.o:: $(DEPS_142)

DEPS_143=source/object/statict3.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
statict3.o:: $(DEPS_143)

DEPS_144=source/object/text.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/graphics/frame.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
text.o:: $(DEPS_144)

DEPS_145=source/object/text1.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/graphics/frame.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
text1.o:: $(DEPS_145)

DEPS_146=source/object/text2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
text2.o:: $(DEPS_146)

DEPS_147=source/object/text3.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
text3.o:: $(DEPS_147)

DEPS_148=source/object/text4.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
text4.o:: $(DEPS_148)

DEPS_149=source/object/text5.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/clip.h include/depui/graphics/frame.h\
	include/depui/macros.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
text5.o:: $(DEPS_149)

DEPS_150=source/object/text6.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
text6.o:: $(DEPS_150)

DEPS_151=source/object/textare2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textare2.o:: $(DEPS_151)

DEPS_152=source/object/textare3.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textare3.o:: $(DEPS_152)

DEPS_153=source/object/textare4.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/desktop/driver.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textare4.o:: $(DEPS_153)

DEPS_154=source/object/textarea.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textarea.o:: $(DEPS_154)

DEPS_155=source/object/textarsc.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/graphics/frame.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textarsc.o:: $(DEPS_155)

DEPS_156=source/object/textlin3.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/graphics/frame.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textlin3.o:: $(DEPS_156)

DEPS_157=source/object/textlin4.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/graphics/frame.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/statict.h include/depui/object/text.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textlin4.o:: $(DEPS_157)

DEPS_158=source/object/textline.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/geometry/geometry.h\
	include/depui/graphics/frame.h include/depui/macros.h\
	include/depui/object/defsize.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/statict.h\
	include/depui/object/text.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
textline.o:: $(DEPS_158)

DEPS_159=source/graphics/vline.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
vline.o:: $(DEPS_159)

DEPS_160=source/graphics/vlines.c include/depui/_config.h include/depui/config.h\
	include/depui/desktop/driver.h include/depui/draw/region.h\
	include/depui/graphics/clip.h include/depui/graphics/draw.h\
	include/depui/macros.h include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
vlines.o:: $(DEPS_160)

DEPS_161=source/object/window.c include/depui/_config.h include/depui/args/args.h\
	include/depui/config.h include/depui/debug/alloc.h\
	include/depui/desktop/desktop.h\
	include/depui/desktop/driver.h include/depui/draw/draw.h\
	include/depui/draw/region.h include/depui/event/event.h\
	include/depui/event/focus.h include/depui/event/queue.h\
	include/depui/geometry/geometry.h\
	include/depui/graphics/decorate.h\
	include/depui/graphics/draw.h include/depui/graphics/frame.h\
	include/depui/macros.h include/depui/object/defsize.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/mover.h\
	include/depui/object/object.h include/depui/object/panel.h\
	include/depui/object/scroll.h include/depui/object/slider.h\
	include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h\
	include/depui/pointer/pointer.h include/depui/support/image.h\
	include/depui/types.h
window.o:: $(DEPS_161)

DEPS_162=source/object/window2.c include/depui/_config.h include/depui/config.h\
	include/depui/debug/alloc.h include/depui/draw/region.h\
	include/depui/event/event.h include/depui/graphics/frame.h\
	include/depui/object/list.h include/depui/object/listdef.h\
	include/depui/object/menu.h include/depui/object/object.h\
	include/depui/object/panel.h include/depui/object/scroll.h\
	include/depui/object/slider.h include/depui/object/window.h\
	include/depui/platform/buffdbl.h\
	include/depui/platform/djvesa1/djvesa1.h\
	include/depui/platform/empty.h\
	include/depui/platform/platform.h\
	include/depui/platform/vtable.h include/depui/support/image.h\
	include/depui/types.h
window2.o:: $(DEPS_162)

ex0.o:: examples/ex0.c
ex1.o:: examples/ex1.c
ex2.o:: examples/ex2.c
ex3.o:: examples/ex3.c
ex4.o:: examples/ex4.c
ex5.o:: examples/ex5.c
ex6.o:: examples/ex6.c
ex7.o:: examples/ex7.c
ex8.o:: examples/ex8.c
ex9.o:: examples/ex9.c
ex10.o:: examples/ex10.c
ex11.o:: examples/ex11.c
ex12.o:: examples/ex12.c
ex13.o:: examples/ex13.c
ex14.o:: examples/ex14.c
ex15.o:: examples/ex15.c
ex16.o:: examples/ex16.c
ex17.o:: examples/ex17.c
ex18.o:: examples/ex18.c
ex19.o:: examples/ex19.c
ex20.o:: examples/ex20.c
ex21.o:: examples/ex21.c
ex22.o:: examples/ex22.c
ex23.o:: examples/ex23.cpp
_ex.o:: examples/_ex.c
