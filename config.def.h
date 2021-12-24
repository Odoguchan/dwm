/* See LICENSE file for copyright and license details. */

#define ICONSIZE 13   /* icon size */
#define ICONSPACING 5 /* space between icon and title */


/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const Gap default_gap        = {.isgap = 1, .realgap = 10, .gappx = 3};
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no standard bar */
static const int topbar             = 1;        /* 0 means standard bar at bottom */
static const int extrabar           = 1;        /* 0 means no extra bar */
static const char statussep         = ';';      /* separator between statuses */
static const char *fonts[] = {
    "Input Sans Compressed:style=Regular:size=8:antialias=true:autohint=true",
    "FiraCode Nerd Font:style=Regular:size=8:antialias=true:autohint=true",
    "Terminus Re33:size=9.5:antialias=true:autohint=true",
    "material-design-icons:pixelsize=11:antialias=true:autohint=true",
    "ocitcons:pixelsize=11:antialias=true:autohint=true",
    "file-icons:pixelsize=11:antialias=true:autohint=true",
    "fontawesome:pixelsize=11:antialias=true:autohint=true",
    "weathericons:pixelsize=11:antialias=true:autohint=true",
    "all-the-icons:pixelsize=11:antialias=true:autohint=true",
    "MesloLGS NF:pixelsize=12:style=Regular"
    "M+ 2m:size=10:style=bold:antialias=true:autohint=true"
    /* "Symbols Nerd Font:size=9:antialias=true:autohint=true" */
};

static const char dmenufont[]       = "monospace:size=10";

/* normal colors */
static const char nor_fg[]	= "#ffffff";
static const char nor_bg[]	= "#222222";
static const char nor_bd[]	= "#444444";
/* selectioned colors */
static const char sel_fg[]	= "#eeeeee";
static const char sel_bg[]	= "#689d6a";
static const char sel_bd[]	= "#689d6a";
/* title colors */
static const char tit_fg[]	= "#ffffff";
static const char tit_bg[]	= "#222222";
static const char tit_bd[]	= "#222222";

static const char *colors[][3]	= {
    /*                  fg      bg      border   */
    [SchemeNorm]	= { nor_fg, nor_bg, nor_bd },
    [SchemeSel]		= { sel_fg, sel_bg, sel_bd },
    [SchemeTitle]	= { tit_fg, tit_bg, tit_bd },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
  /* class | instance | title | tags | mask | isfloating | monitor  */
    { "Gimp",			 NULL,  NULL,	0,	1,	-1 },
    { "Firefox",		 NULL,  NULL,	1 << 3,	0,	-1 },
    { "luakit",			 NULL,  NULL,	1 << 3,	0,	-1 },
    { "TelegramDesktop", NULL,  NULL,	1 << 4,	0,	-1 },
    { "qutebrowser",	 NULL,  NULL,	1 << 3,	0,	-1 },
    { "*EQUAKE*[eDP-1]", NULL,  NULL,	0,	0,	-1 },
    { "Event Tester",    NULL,  NULL,	0,	1,	-1 }
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      doubledeck },
    { NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "run", NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	/* { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } }, */
	/* { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } }, */
    { MODKEY|ControlMask,      XK_b,         togglebar,      {0} },
    { MODKEY|ControlMask,      XK_b,         toggleextrabar, {0} },
    /* up and down on the stack */
    { MODKEY,                  XK_e,         focusstack, {.i = +1 } },
    { MODKEY,                  XK_i,         focusstack, {.i = -1 } },
    { MODKEY,                  XK_Down,      focusstack, {.i = +1 } },
    { MODKEY,                  XK_Up,        focusstack, {.i = -1 } },

    /* move window up and down on the stack */
    { MODKEY|ShiftMask,        XK_e,         movestack,  {.i = +1 } },
    { MODKEY|ShiftMask,        XK_i,         movestack,  {.i = -1 } },

    /* increase and decrease the  number of windows on master stack */
    { MODKEY|ControlMask,      XK_n,         incnmaster, {.i = +1 } },
    { MODKEY|ControlMask,      XK_o,         incnmaster, {.i = -1 } },

    /* increase and decrease the window size */
    { MODKEY,                  XK_n,         setmfact, {.f = -0.05} },
    { MODKEY,                  XK_o,         setmfact, {.f = +0.05} },
    { MODKEY,                  XK_Left,      setmfact, {.f = -0.05} },
    { MODKEY,                  XK_Right,     setmfact, {.f = +0.05} },


	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_d,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                  XK_space,     cyclelayout,    {.i = -1 } },
    { MODKEY|ControlMask,      XK_space,     cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,        XK_space,     togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    /* multi-monitor stuff */
    { MODKEY,                  XK_comma,     focusmon, {.i = -1 } },
    { MODKEY,                  XK_period,    focusmon, {.i = +1 } },
    { MODKEY|ShiftMask,        XK_comma,     tagmon,   {.i = -1 } },
    { MODKEY|ShiftMask,        XK_period,    tagmon,   {.i = +1 } },

	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_Escape,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarLeftStatus,   0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarMiddle,       0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkExBarRightStatus,  0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkClientWin,   MODKEY,         Button4,     focusstack,     {.i = +1 } },
    { ClkClientWin,   MODKEY,         Button5,     focusstack,     {.i = -1 } },
};

