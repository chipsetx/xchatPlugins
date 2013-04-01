/*
 * Author: Harry van Haaren, 2013
 *         harryhaaren@gmail.com
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

// compile: 
// gcc -shared -fPIC `pkg-config --cflags --libs libnotify` xchatNotify.c -o libnotify_hilight.so

// copy to ~/.xchat/ for automatic loading on startup
// manual loading / unloading can be done from:
// XChat->Window->Plugins and Scripts

#include "xchat-plugin.h"

#include <stdio.h>
#include <libnotify/notify.h>

#define PNAME "Xchat NickMSG Notify"
#define PDESC "Notifies of when somebody calls your Nick"
#define PVERSION "0.1"

static xchat_plugin *ph;   /* plugin handle */
static int enable = 1;

static int join_cb(char *word[], void *userdata)
{
   if (enable)
      /* Op ANYONE who joins */
      xchat_commandf(ph, "OP %s", word[1]);
   /* word[1] is the nickname, as in the Settings->Advanced->TextEvents window in xchat */

   return XCHAT_EAT_NONE;  /* don't eat this event, xchat needs to see it! */
}

static int autooptoggle_cb(char *word[], char *word_eol[], void *userdata)
{
   if (!enable)
   {
      enable = 1;
      xchat_print(ph, "AutoOping now enabled!\n");
   } else
   {
      enable = 0;
      xchat_print(ph, "AutoOping now disabled!\n");
   }

   return XCHAT_EAT_ALL;   /* eat this command so xchat and other plugins can't process it */
}

void xchat_plugin_get_info(char **name, char **desc, char **version, void **reserved)
{
   *name = PNAME;
   *desc = PDESC;
   *version = PVERSION;
}

static int hilight_cb(char *word[], void *userdata)
{
  NotifyNotification * tagged = notify_notification_new ("XChat:", "Tagged message", "dialog-information");
  notify_notification_set_timeout (tagged, 5000);
  notify_notification_show (tagged, NULL);
  
  //printf("notify: %i\n", strlen(word[2]) );
  
  return XCHAT_EAT_NONE;
}


int xchat_plugin_init(xchat_plugin *plugin_handle,
                      char **plugin_name,
                      char **plugin_desc,
                      char **plugin_version,
                      char *arg)
{
   /* we need to save this for use with any xchat_* functions */
   ph = plugin_handle;

   /* tell xchat our info */
   *plugin_name = PNAME;
   *plugin_desc = PDESC;
   *plugin_version = PVERSION;

   notify_init ("Hello world!");

   //xchat_hook_command(ph, "AutoOpToggle", XCHAT_PRI_NORM, autooptoggle_cb, "Usage: AUTOOPTOGGLE, Turns OFF/ON Auto Oping", 0);
   //xchat_hook_print(ph, "Join", XCHAT_PRI_NORM, join_cb, 0);

   xchat_hook_print(ph, "Channel Msg Hilight", XCHAT_PRI_NORM, hilight_cb, NULL);

   xchat_print(ph, "libnotify plugin loaded successfully!\n");

   return 1;       /* return 1 for success */
}
