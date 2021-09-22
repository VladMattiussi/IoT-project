package it.unibo.isi.seeiot.taskexample.ui;

import android.os.Bundle;
import android.os.Looper;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;
import android.widget.TextView;

import it.unibo.isi.seeiot.taskexample.R;
import it.unibo.isi.seeiot.taskexample.agents.Agent;
import it.unibo.isi.seeiot.taskexample.agents.AgentAsAsyncTask;
import it.unibo.isi.seeiot.taskexample.agents.AgentWithHandler;
import it.unibo.isi.seeiot.taskexample.agents.AgentWithRunOnUiThread;
import it.unibo.isi.seeiot.taskexample.agents.AgentWithWrongThreadException;
import it.unibo.isi.seeiot.taskexample.handlers.MainUiHandler;

public class MainActivity extends AppCompatActivity {

    private TextView counterLabel;
    private Button upButton, downButton, stopButton;

    private Agent agent;
    private AgentAsAsyncTask agentTask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        initUI();
    }

    @Override
    protected void onResume() {
        super.onResume();

        agent = new AgentWithWrongThreadException(counterLabel);
        //agent = new AgentWithRunOnUiThread(this, counterLabel);
        //agent = new AgentWithHandler(new MainUiHandler(Looper.getMainLooper(), counterLabel));

        new Thread(agent).start();

        //agentTask = new AgentAsAsyncTask(counterLabel);
        //agentTask.execute();
    }

    private void initUI(){
        counterLabel = findViewById(R.id.counterLabel);

        upButton = findViewById(R.id.upButton);
        upButton.setOnClickListener(view1 -> upButtonOnClickEvent());

        downButton = findViewById(R.id.downButton);
        downButton.setOnClickListener(view -> downButtonOnClickEvent());

        stopButton = findViewById(R.id.stopButton);
        stopButton.setOnClickListener(view -> stopButtonOnClickEvent());

        upButton.setEnabled(false);
        downButton.setEnabled(true);
        stopButton.setEnabled(true);
    }

    private void upButtonOnClickEvent(){
        agent.countUp();
        //agentTask.countUp();

        upButton.setEnabled(false);
        downButton.setEnabled(true);
    }

    private void downButtonOnClickEvent(){
        agent.countDown();
        //agentTask.countDown();

        upButton.setEnabled(true);
        downButton.setEnabled(false);
    }

    private void stopButtonOnClickEvent(){
        agent.stop();
        //agentTask.stop();

        upButton.setEnabled(false);
        downButton.setEnabled(false);
        stopButton.setEnabled(false);
    }
}
