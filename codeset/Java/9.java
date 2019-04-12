package server.main;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

/**
 * Launcher is the main class. You start the server by executing this
 * class' main method, optionally passing a valid configuration file as
 * an argument. If no argument is present, it is assumed that the
 * configuration file will be iss.conf in the project root.
 * 
 * @author Adrian Petrescu
 *
 */
public class Launcher {

	private static final String defaultConfigFileName = "iss.conf";

	private static final String userPrefix = "user_";
	private static final String databasePrefix = "db_";
	private static final String connectionPrefix = "conn_";
	private static final String protocolPrefix = "protocol_";

	public static void main(String[] args) {
		String configFileName = (args.length == 0) ? defaultConfigFileName : args[0];
		Properties config = new Properties();
		String[] keys = new String[0];

		try {
			InputStream in = new FileInputStream(new File(configFileName));
			config.load(in);
			keys = new String[config.size()];
			config.keySet().toArray(keys);
			in.close();
		} catch (FileNotFoundException e) {
			System.err.println("Configuration file not found: " + configFileName);
			System.err.println("ISS needs a valid configuration file to launch.");
			System.exit(-1);
		} catch (IOException e) {
			System.err.println("Configuration file could not be read: " + configFileName);
			System.err.println("ISS needs a valid configuration file to launch.");
			System.exit(-1);
		}
		Properties userConfig = new Properties();
		Properties databaseConfig = new Properties();
		Properties connectionConfig = new Properties();
		Properties protocolConfig = new Properties();
		
		/* Load Connection configuration */
		for (String key : keys) {
			if (key.startsWith(connectionPrefix)) {
				connectionConfig.put(key.substring(connectionPrefix.length()), config.get(key));
			} else if (key.startsWith(databasePrefix)) {
				databaseConfig.put(key.substring(databasePrefix.length()), config.get(key));
			} else if (key.startsWith(userPrefix)) {
				userConfig.put(key.substring(userPrefix.length()), config.get(key));
			} else if (key.startsWith(protocolPrefix)) {
				protocolConfig.put(key.substring(protocolPrefix.length()), config.get(key));
			}
		}
		System.out.println("Configuration loaded.");
		
		System.out.print("Starting server ... ");
		Server server = new Server(databaseConfig, connectionConfig, userConfig, protocolConfig);
		System.out.println("done!");
		server.process();
	}

}
