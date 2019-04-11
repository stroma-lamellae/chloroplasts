package server.main;

import java.util.NoSuchElementException;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

import server.services.protocol.OutputMessageQueue;


/**
 * A threadsafe global queue of all the messages ready to be sent to clients
 * connected to the server. The server is constantly processing this queue.
 * 
 * The queue uses Round-Robin scheduling; that is, messages of higher priority
 * are always dequeued before messages of lower priority, and it follows a FIFO
 * scheme for messages with the same priority.
 * 
 * @author Adrian Petrescu
 */
public class GlobalOutputMessageQueue {

	private static GlobalOutputMessageQueue self;
	/**
	 * Singleton accessor to the GlobalOutputMessageQueue. If the queue has not
	 * yet been accessed, it will be created.
	 * 
	 * @return A reference to the GlobalOutputMessageQueue.
	 */
	public static GlobalOutputMessageQueue getGlobalOutputMessageQueue() {
		if (self == null) {
			self = new GlobalOutputMessageQueue();
		}
		return self;
	}
	
	protected Queue<OutputMessageQueue> lowPriorityOutputMessageQueue;
	protected Queue<OutputMessageQueue> medPriorityOutputMessageQueue;
	protected Queue<OutputMessageQueue> highPriorityOutputMessageQueue;
	
	/**
	 * Creates a new instance of GlobalOutputMessageQueue.
	 */
	protected GlobalOutputMessageQueue() {
		lowPriorityOutputMessageQueue = new ConcurrentLinkedQueue<OutputMessageQueue>();
		medPriorityOutputMessageQueue = new ConcurrentLinkedQueue<OutputMessageQueue>();
		highPriorityOutputMessageQueue = new ConcurrentLinkedQueue<OutputMessageQueue>();
	}
	
	/**
	 * Add a message to the global queue. 
	 * 
	 * @param message The message to be queued up.
	 */
	@SuppressWarnings("deprecation")
	public synchronized void enqueue(OutputMessageQueue message) {
		boolean unlockListener = this.isEmpty();
		switch (message.getPriority()) {
			case 0: lowPriorityOutputMessageQueue.add(message);
					break;
			case 1: medPriorityOutputMessageQueue.add(message);
					break;
			case 2: medPriorityOutputMessageQueue.add(message);
					break;
		}
		if (unlockListener) {
			Thread[] threads = new Thread[Thread.currentThread().getThreadGroup().activeCount()];
			Thread.currentThread().getThreadGroup().enumerate(threads);
			for (int i = 0; i < threads.length; i++) {
				if (threads[i].getName().equals("OutputQueueProcessor")) {
					threads[i].resume();
					return;
				}
			}
		}
	}
	
	/**
	 * @return The oldest message of the highest priority available, or NULL if the
	 * queue is empty.
	 */
	public synchronized OutputMessageQueue dequeue() {
		try {
			return highPriorityOutputMessageQueue.remove();
		} catch (NoSuchElementException noHigh) {
			try {
				return medPriorityOutputMessageQueue.remove();
			} catch (NoSuchElementException noMed) {
				try {
					return lowPriorityOutputMessageQueue.remove();
				} catch(NoSuchElementException noLow) {}
			}
		}
		return null;
	}
	
	
	/**
	 * Return the total number of output message queues still queued up
	 * in the global buffer, of all priorities.
	 * 
	 * @return The total number of queued OutputMessageStacks.
	 */
	public int getSize() {
		return lowPriorityOutputMessageQueue.size() +
				medPriorityOutputMessageQueue.size() +
				highPriorityOutputMessageQueue.size();
	}
	
	/**
	 * Return the total number of output message queues still in the queue
	 * with a given priority.
	 * 
	 * @param priority The priority level of counted messages.
	 * @return The total number of queued OutputMessageStacks of the given
	 * priority.
	 */
	public int getSize(int priority) {
		switch (priority) {
			case 0: return lowPriorityOutputMessageQueue.size();
			case 1: return medPriorityOutputMessageQueue.size();
			case 2: return highPriorityOutputMessageQueue.size();
			default: return 0;
		}
	}
	
	/**
	 * Returns <code>true</code> if the queue contains no elements of any
	 * priority.
	 * 
	 * @return <code>true</code> if the queue is completely empty.
	 */
	public synchronized boolean isEmpty() {
		return lowPriorityOutputMessageQueue.isEmpty()
				&& medPriorityOutputMessageQueue.isEmpty()
				&& highPriorityOutputMessageQueue.isEmpty();
	}
	
	/**
	 * Returns <code>true</code> if the queue contains no elements of the
	 * given priority.
	 * 
	 * @param priority The priority level to check.
	 * @return <code>true</code> if the queue is empty of messages of the given
	 * priority.
	 */
	public boolean isEmpty(int priority) {
		switch (priority) {
		case 0:
			return lowPriorityOutputMessageQueue.isEmpty();
		case 1:
			return medPriorityOutputMessageQueue.isEmpty();
		case 2:
			return highPriorityOutputMessageQueue.isEmpty();
		default:
			return true;
		}
	}
	
}
