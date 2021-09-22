package it.unibo.isi.seeiot.taskexample.agents;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import it.unibo.isi.seeiot.taskexample.handlers.MainUiHandler;

public class AgentWithHandler extends AbstractAgent {
    private final Handler uiHandler;

    public AgentWithHandler(final Handler uiHandler){
        this.uiHandler = uiHandler;
    }

    @Override
    void updateCounter(int value) {
        sendMessageToHandler(value);
    }

    private void sendMessageToHandler(int value){
        final Bundle b = new Bundle();
        b.putInt(MainUiHandler.NEW_CNT_VALUE, value);

        final Message msg = new Message();
        msg.what = MainUiHandler.NEW_CNT_VALUE_MSG;
        msg.setData(b);

        uiHandler.sendMessage(msg);
    }
}
