import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;
import java.util.Random;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;
/**
 * The GameComponent is class like a screen that is inside the frame and all the methods such a creature, predator, prey, fastprey is being called here.
 * GameComponent extends JPanel in order to use the paintComponent which is essential for drawing the object.  
 * @author Semir
 */
public class GameComponent extends JPanel
{
	//Instance Variables
	private ArrayList<Creature> creature;//Creating an AraayList<Object> where the object is Creature, which it contains all the memory of the creature.java etc methods.
	private int timer;//A counter for time.
	private int count = 0;//A counter for number of objects being removed.
	final int NUMBER_CIRCLES=20;//Number of circles to appear in the screen.
	private int DELAY=10;//A time delay for ActionListneer
	Timer t;//Initializing a Timer from java api
	
	Random random= new Random();//Creating a random generator to assign it with object to appear in random with frame's width.
	
	//Creating objects of Creature's subclass to be called later in the constructor
	Predator predator=null;
	Prey prey=null;
	FastPrey fastPrey =null;
	/**
	 * Constructor where initializing all the instance variable such as the length of its size and position.
	 */
	public GameComponent()
	{
		//Finishing the construction of an ArrayList<Object>
		creature = new ArrayList<Creature>();
		//Initializing all the variable to the my preference.
		int x = 200;
		int y = 200;
		int size = 100 ;
		timer=0;
		count=-1;
		
		//Creating objects to appear in the screen by casting a for-loop		
		for(int i = 0; i < NUMBER_CIRCLES; i++)
   	    {
   	    	//int xRand = random.nextInt(GameViewer.getFrameWidth());
   	    	//int yRand = random.nextInt(GameViewer.getFrameWidth());
   	    	int xRand = random.nextInt(GameViewer.WIDTH);
   	    	int yRand = random.nextInt(GameViewer.WIDTH);
			prey = new Prey(xRand,yRand, size/4,size/4);
   	    	creature.add(prey);//Adding the new updated info to the list
   	    }
		//Creating objects to appear in the screen by casting a for-loop	
		for(int j =0; j <NUMBER_CIRCLES/4;j++)
		{
			int xRand = random.nextInt(GameViewer.WIDTH);
   	    	int yRand = random.nextInt(GameViewer.WIDTH);
   	    	fastPrey = new FastPrey(xRand,yRand, size/3,size/3);
   	    	creature.add(fastPrey);//Adding the new updated info to the list
		}
		//Creating an object to appear in the screen in this case 1 should be the predator 
		predator = new Predator(x,y,size/2,size/2);
		creature.add(predator);//Adding the new updated info to the list
		
		/**
		 * Ignore this part of the code, this was an just an experiment that I have tried to do.
		 * @author Semir
		 */
		class keyBoredListener implements KeyListener
		{
			//This is for keyboard input
		 	@Override
			public void keyPressed(KeyEvent e) {
		 		int c = e.getKeyCode();
		 		System.out.println("KeyInputed " +c );
		 		if(c == KeyEvent.VK_LEFT)
				{
					predator.turnLeft();
				}
				if(c== KeyEvent.VK_RIGHT)
				{	
					predator.turnRight();
				}
			}
			@Override
			public void keyReleased(KeyEvent e) {
			}
			@Override
			public void keyTyped(KeyEvent e) {
				}
		}
		KeyListener input = new keyBoredListener();
		addKeyListener(input);
		
		
		/**
		 * This class implements MouseListener from java's api in this class it allows the grab user's input, in this case its the mouse  
		 * @author Semir
		 *
		 */
		class ClickListener implements MouseListener{
		 	
			//This is for mouse 
			@Override
			public void mouseClicked(MouseEvent e) {
				if(e.getButton() == e.BUTTON1) //Checks to see if the right button has been clicked.
				{
					predator.turnLeft();//Calls the method from predator.
					t.start();//Start the timer class.
				}
				else if(e.getButton() == e.BUTTON3){//Checks to see if the right button has been clicked.
					predator.turnRight();//Calls the method from predator.
					t.start();//Start the timer class.
				}
			}
			public void mouseReleased(MouseEvent e){}
			public void mouseEntered(MouseEvent e){}
		 	public void mouseExited(MouseEvent e){}
		 	public void mousePressed(MouseEvent e){}
			
		
		}
		MouseListener mpListener = new ClickListener();
		addMouseListener(mpListener);
		
		/**
		 * This class implements ActionListener from java's api in this class it allows the action to move, like animation.  
		 * @author Semir
		 */
		class TimerListener implements ActionListener
		{
			@Override
			public void actionPerformed(ActionEvent event) 
			{
				
				for(Creature creatObject : creature)//For each loop 
				{
			    timer+=20; //Increment timer
				creatObject.move();//Move method from the creatObject/Creature
				}
				repaint();//Repaint after the for loop
			}
			
		}
		ActionListener timerListener = new TimerListener();
		t = new Timer(DELAY, timerListener);//Create timer with tiemrListener method
		
		
		}
	/**
	 * Draw out all objects in the frame.
	 */
	public void paintComponent(Graphics g)
	{
		super.paintComponent(g); //Call the super component from graphics
		Graphics2D g2 = (Graphics2D)g;//Casting
		
		for(Creature creatObject: creature)//For each loop  creating 
		{
				//predator.draw(g2); //Experimenting
				//creatur.draw(g2);//Experimenting
				if(creatObject.checkAlive())
				{
					predator.draw(g2);//Draw the predator
					creatObject.draw(g2);//Draw the all other objects
					if(creatObject.collide(predator))
					{
					creatObject.delete();//Call the method to delete the object
					count++;
						if(count == 25 )
						{
							
							t.stop();//Time stop
						}
					}
				}
		}
		//This is a format conversation for time
		int milseconds = (int) (timer / 1000) % 60 ;
		int seconds = (int) ((timer / (1000*60)) % 60);
		int minutes   = (int) ((timer/ (1000*60*60)) % 24);
		
		g2.setColor(Color.blue); //Set the text in color blue
	
		g2.drawString("TIME: "+ minutes + ":" +seconds+":"+milseconds, 5, 15); //Draws out the string
		g2.drawString("| POINTS: "+count,85,15);//Draws out the string
		g2.drawRect(0, 0, 160, 20);//Draws out a rectangle shape around the string
		
	}
		
	
}