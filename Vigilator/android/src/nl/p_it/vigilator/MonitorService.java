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

import android.content.Intent;
import org.qtproject.qt.android.bindings.QtService;
import android.app.job.JobInfo;
import android.app.job.JobScheduler;
import android.content.ComponentName;
import android.content.Context;
import android.util.Log;
import android.widget.Toast;
import static android.content.Context.JOB_SCHEDULER_SERVICE;

public class MonitorService {

    private static final String TAG = MonitorService.class.getSimpleName();

    public static void scheduleMonitorJobs(final Context context) {
        ComponentName componentName = new ComponentName(context, HealthTesterService.class);
        JobInfo info = new JobInfo.Builder(1, componentName)
                .setRequiredNetworkType(JobInfo.NETWORK_TYPE_ANY)
                .setPersisted(true)
                .setPeriodic(JobInfo.getMinPeriodMillis(), JobInfo.getMinFlexMillis())
                .build();

        JobScheduler scheduler = (JobScheduler) context.getSystemService(JOB_SCHEDULER_SERVICE);

        int resultCode = scheduler.schedule(info);
        if (resultCode == JobScheduler.RESULT_SUCCESS) {
            Log.i(TAG, "Monitor job scheduled");
        } else {
            NotificationClient.notify(context, "Monitor job could not be scheduled!");
        }
    }
}
