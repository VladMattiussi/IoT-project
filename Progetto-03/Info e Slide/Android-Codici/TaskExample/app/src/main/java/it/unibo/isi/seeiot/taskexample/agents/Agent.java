package it.unibo.isi.seeiot.taskexample.agents;

public interface Agent extends Runnable{
    void countUp();
    void countDown();
    void stop();
}
