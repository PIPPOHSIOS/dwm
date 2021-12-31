/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int gappx     = 7;        /* gaps between windows */
static const unsigned int snap      = 16;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/bar.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "Helvetica Neue:style=Medium:size=12" };
static const char dmenufont[]       = "Helvetica Neue:style=Medium:size=12";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";

#include "theme.h"
static const char *colors[][3]      = {
    /*               fg     bg     border   */
    [SchemeNorm] = { white, black, gray1 },
    [SchemeSel]  = { white, black, gray2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
    { "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
    { "firefox", NULL,     NULL,           1 << 4,    0,          0,          -1,        -1 },
    { "URxvt",   NULL,     NULL,           0,         0,          1,           0,        -1 },
    { "discord", NULL,     NULL,           1 << 3,    0,          0,           0         -1 },
    { NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[]=",      tile },    /* first entry is default */
    { "><>",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[@]",      spiral },
    { "[\\]",     dwindle },
};

/* key definitions */
// Mod1Mask - Alt key
// Mod4Mask - Super key
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
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", black, "-nf", white, "-sb", gray2, "-sf", white, NULL };
static const char *roficmd[]  = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include "movestack.c"
static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_c,      spawn,          {.v = roficmd } },
    { MODKEY,             			XK_Return, spawn,          {.v = termcmd } },

    { MODKEY,                       XK_t,      togglebar,      {0} },

    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },

    { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },

    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },

    { MODKEY,             			XK_q,      killclient,     {0} },

    { MODKEY,                       XK_F1,     setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_F2,     setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_F3,     setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_F4,     setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_F5,     setlayout,      {.v = &layouts[4]} },

    { MODKEY|ShiftMask,             XK_space,  setlayout,      {0} },
    { MODKEY|Mod1Mask|ShiftMask,    XK_space,  togglefloating, {0} },

    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

    { MODKEY,                       XK_Left,  focusmon,        {.i = -1 } },
    { MODKEY,                       XK_Right, focusmon,        {.i = +1 } },
    { MODKEY|ShiftMask,             XK_Left,  tagmon,          {.i = -1 } },
    { MODKEY|ShiftMask,             XK_Right, tagmon,          {.i = +1 } },

    { MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    TAGKEYS(                        XK_8,                      7)
    TAGKEYS(                        XK_9,                      8)
    
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};

