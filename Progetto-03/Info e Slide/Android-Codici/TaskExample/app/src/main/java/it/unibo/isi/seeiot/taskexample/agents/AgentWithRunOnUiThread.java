package it.unibo.isi.seeiot.taskexample.agents;

import android.app.Activity;
import android.widget.TextView;

import java.util.Locale;

public class AgentWithRunOnUiThread extends AbstractAgent {

    private Activity activity;
    private TextView label;

    public AgentWithRunOnUiThread(final Activity activity, final TextView label){
        this.activity = activity;
        this.label = label;
    }

    @Override
    void updateCounter(int value) {
        activity.runOnUiThread(() -> label.setText(String.format(Locale.ITALY, "%d", value)));
    }
}
