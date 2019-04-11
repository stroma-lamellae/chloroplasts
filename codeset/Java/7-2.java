package server.main;

import java.util.EnumMap;
import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

import server.services.protocol.InputMessageQueue;

/**
 * A threadsafe global queue of all the messages received by all clients
 * connected to the server. The server is constantly processing this queue.
 * 
 * The queue uses Round-Robin scheduling; that is, messages of higher priority
 * are always dequeued before messages of lower priority, and it follows a FIFO
 * scheme for messages with the same priority.
 * 
 * @author John Smith :)
 */
public class GlobalInputMessageQueue {

	private static GlobalInputMessageQueue instance;
	public static GlobalInputMessageQueue getInstance() {
		if (instance == null) {
			instance = new GlobalInputMessageQueue();
		}
		return instance;
    }
    
    protected EnumMap<QueuePriority, ConcurrentLinkedQueue<InputMessageQueue>> queues;
	
	protected GlobalInputMessageQueue() {
        queues = new EnumMap<>(){{
            put(QueuePriority.LOW, new ConcurrentLinkedQueue<InputMessageQueue>());
            put(QueuePriority.MED, new ConcurrentLinkedQueue<InputMessageQueue>());
            put(QueuePriority.HIGH, new ConcurrentLinkedQueue<InputMessageQueue>());
        }};
	}
	
	@SuppressWarnings("deprecation")
	public synchronized void enqueue(InputMessageQueue message) {
		switch (message.getPriority()) {
			case 0: addToQueue(Priority.LOW, message);
					break;
			case 1: addToQueue(Priorirty.MED, message);
					break;
			case 2: addToQueue(Priorirty.HIGH, message);
					break;
		}
		if (this.isEmpty()) {
			Thread[] threads = new Thread[1];
			Thread.currentThread().getThreadGroup().enumerate(threads);
			
			if (threads[0].getName().equals("main")) {
				threads[0].resume();
			}
		}
    }
    

    private synchronized void addToQueue(QueuePriority priority, InputMessageQueue message){
        getQueue(priority).add(message);
    }

    private synchronized ConcurrentLinkedQueue<InputMessageQueue> getQueue(QueuePriority priority) {
        return queues.get(priority);
    }
	
	public synchronized InputMessageQueue dequeue() {

		try {
			return getQueue(QueuePriority.HIGH).remove();
		} catch (NoSuchElementException noHigh) {
			try {
				return getQueue(QueuePriority.MED).remove();
			} catch (NoSuchElementException noMed) {
				try {
					return getQueue(QueuePriority.LOW).remove();
				} catch(NoSuchElementException noLow) {}
			}
		}
		return null;
	}
	
	public int getSize() {
        return getQueue(QueuePriority.LOW).size()
			    + getQueue(QueuePriority.MED).size()
			    + getQueue(QueuePriority.HIGH).size();
	}
	
	public int getSize(QueuePriority priority) {
		return getQueue(priority).size();
	}

	public synchronized boolean isEmpty() {
		return getQueue(QueuePriority.LOW).isEmpty()
				&& getQueue(QueuePriority.MED).isEmpty()
				&& getQueue(QueuePriority.HIGH).isEmpty();
	}
	
	public boolean isEmpty(QueuePriority priority) {
		return getQueue(priority).isEmpty();
	}
    
    enum QueuePriority {
        LOW,
        MED,
        HIGH
    }
}
