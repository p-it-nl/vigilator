/**
 * Copyright (c) p-it
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package nl.p_it.vigilator;

import android.app.Notification;
import android.app.NotificationManager;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.BitmapFactory;
import android.app.NotificationChannel;

public class NotificationClient
{
    public static void notify(final Context context, final String message) {
        try {

            // futurework notification on click open

            NotificationManager notificationManager = (NotificationManager)
                    context.getSystemService(Context.NOTIFICATION_SERVICE);

            Notification.Builder builder;
            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.O) {
                int importance = NotificationManager.IMPORTANCE_HIGH;
                NotificationChannel notificationChannel;
                notificationChannel = new NotificationChannel("Vigilator", "Vigilator notifier", importance);
                notificationManager.createNotificationChannel(notificationChannel);
                builder = new Notification.Builder(context, notificationChannel.getId());
            } else {
                builder = new Notification.Builder(context);
            }

            Bitmap icon = BitmapFactory.decodeResource(context.getResources(), R.drawable.icon);
            builder.setSmallIcon(R.drawable.icon)
                    .setLargeIcon(icon)
                    .setContentTitle("An application has become unhealthy!")
                    .setContentText(message)
                    .setDefaults(Notification.DEFAULT_ALL)
                    .setColor(Color.MAGENTA)
                    .setAutoCancel(false);

            notificationManager.notify(0, builder.build());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
