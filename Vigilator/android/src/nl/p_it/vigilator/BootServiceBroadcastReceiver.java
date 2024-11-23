package nl.p_it.vigilator;

import android.content.Context;
import android.content.Intent;
import android.content.BroadcastReceiver;

public class BootServiceBroadcastReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(final Context context, final Intent intent) {
        Intent startServiceIntent = new Intent(context, MonitorService.class);
        context.startService(startServiceIntent);
    }
}
