package it.unibo.isi.seeiot.taskexample.agents;

import android.widget.TextView;

import java.util.Locale;

public class AgentWithWrongThreadException extends AbstractAgent {
    private TextView label;

    public AgentWithWrongThreadException(final TextView label){
        this.label = label;
    }

    @Override
    void updateCounter(int value) {
        label.setText(String.format(Locale.ITALY, "%d", value));
    }
}
