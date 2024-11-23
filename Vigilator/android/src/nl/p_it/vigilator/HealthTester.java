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

import android.content.Context;
import android.util.Log;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class HealthTester {

    private static final String TAG = HealthTester.class.getSimpleName();

    public void test(final Context context) {
        try {
            URL url = new URL("https://localhost:48/monitor");
            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setRequestMethod("GET");

            byte[] data;
            try (InputStream input = urlConnection.getInputStream(); ByteArrayOutputStream output = new ByteArrayOutputStream()) {
                final byte[] buffer = new byte[8192];
                for (int count; (count = input.read(buffer)) > 0; ) {
                    output.write(buffer, 0, count);
                }
                data = output.toByteArray();
            }

            String result = new String(data);

            List<String> allMatches = new ArrayList<>();
            Matcher m = Pattern.compile("\"ACTIVE\"")
                    .matcher(result);
            while (m.find()) {
                allMatches.add(m.group());
            }

            if (allMatches.size() != 8) {
                NotificationClient.notify(context, "{Name} is failing health check");
            }

            Log.i(TAG, "Result is ok");
        } catch (IOException ex) {
            Log.e(TAG, "Exception ", ex);
        }
    }
}
