#include <stdlib.h>
#include <grx20.h>
#include "grchart.h"

int GRXMain()
{
    GrChartData d;
    GrChartStyle s;
    double v[12] = { 3.0, 5.0, 2.7, 4.2, 1.6, 8.1,
                     2.7, 3.9, 4.1, 7.9, 0.6, 7.2 };
    char *xlabels[6] = { "one", "two", "three", "four", "five", "six" };
    char *slabels[2] = { "ser1", "ser2" };
    GrContext *ctx;
    int maxx, maxy;

    GrSetMode(GR_default_graphics);

    d.title = "Chart Title";
    d.xtitle = "X-Axis Title";
    d.ytitle = "Y-Axis Title";
    d.ymin = 0.0;
    d.ymax = 10;
    d.ystep = 0.5;
    d.ylabelstep = 1.0;
    d.nsamples = 6;
    d.nseries = 2;
    d.yvalues = v;
    d.xlabels = xlabels;
    d.slabels = slabels;

    GrChartSetDefaultStyle(&s);
    s.cbg = GrAllocColor(200, 200, 200);
    s.cvalues[0] = GrAllocColor(0, 127, 0);
    s.cvalues[1] = GrAllocColor(127, 0, 0);

    GrChartDraw(NULL, &d, &s);

    GrKeyRead();

    maxx = GrSizeX();
    maxy = GrSizeY();

    ctx = GrCreateSubContext(0, 0, maxx/2-1, maxy/2-1, NULL, NULL);
    s.type = GR_CHART_TYPE_LINES;
    d.title = "Chart Title (LINES)";
    GrChartDraw(ctx, &d, &s);

    ctx = GrCreateSubContext(maxx/2, 0, maxx-1, maxy/2-1, NULL, NULL);
    s.type = GR_CHART_TYPE_AREALINES;
    d.title = "Chart Title (AREALINES)";
    GrChartDraw(ctx, &d, &s);

    s.cvalues[0] = GrAllocColor(0, 0, 127);
    s.cvalues[1] = GrAllocColor(0, 127, 127);

    ctx = GrCreateSubContext(0, maxy/2, maxx/2-1, maxy-1, NULL, NULL);
    s.type = GR_CHART_TYPE_BARS;
    d.title = "Chart Title (BARS)";
    GrChartDraw(ctx, &d, &s);

    ctx = GrCreateSubContext(maxx/2, maxy/2, maxx-1, maxy-1, NULL, NULL);
    s.type = GR_CHART_TYPE_AREAS;
    d.title = "Chart Title (AREAS)";
    GrChartDraw(ctx, &d, &s);

    GrHLine(0, maxx-1, maxy/2,s.cfg);
    GrVLine(maxx/2, 0, maxy-1,s.cfg);
    
    GrKeyRead();

    d.ymax = 20;
    s.cvalues[0] = GrAllocColor(127, 0, 127);
    s.cvalues[1] = GrAllocColor(127, 127, 0);

    ctx = GrCreateSubContext(0, 0, maxx/2-1, maxy-1, NULL, NULL);
    s.type = GR_CHART_TYPE_ACUBARS;
    d.title = "Chart Title (ACUBARS)";
    GrChartDraw(ctx, &d, &s);

    ctx = GrCreateSubContext(maxx/2, 0, maxx-1, maxy-1, NULL, NULL);
    s.type = GR_CHART_TYPE_ACUAREAS;
    d.title = "Chart Title (ACUAREAS)";
    GrChartDraw(ctx, &d, &s);

    GrVLine(maxx/2, 0, maxy-1,s.cfg);

    GrKeyRead();

    return 0;
}
