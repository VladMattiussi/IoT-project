package it.unibo.isi.seeiot.taskexample.agents;

public abstract class AbstractAgent implements Runnable, Agent {
    private volatile boolean up = true;
    private volatile boolean stop = false;

    @Override
    public void run() {

        int cnt = 0;

        while(!stop){
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            if(up){
                cnt = cnt + 1;
            } else {
                cnt = cnt - 1;
            }

            updateCounter(cnt);
        }
    }

    @Override
    public void countUp(){
        up = true;
    }

    @Override
    public void countDown(){
        up = false;
    }

    @Override
    public void stop(){
        stop = true;
    }

    abstract void updateCounter(final int value);
}
