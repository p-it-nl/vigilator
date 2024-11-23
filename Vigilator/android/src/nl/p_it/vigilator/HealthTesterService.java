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

import android.app.job.JobParameters;
import android.util.Log;
import android.app.job.JobService;

public class HealthTesterService extends JobService {

    @Override
    public boolean onStartJob(final JobParameters params) {
        Log.i(HealthTesterService.class.getSimpleName(), "Starting tester");

        new Thread(() -> {
            try {
                new HealthTester().test(this);
            }
            catch (Exception ex) {
                ex.printStackTrace();
            }
        }).start();

        return true;
    }

    @Override
    public boolean onStopJob(final JobParameters params) {
        // nothing to do here
        return true;
    }
}
