package com.example.rovercommand;

import java.io.IOException;
import java.io.OutputStream;
import java.util.UUID;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.Toast;

public class Main extends Activity {
  private static final String TAG = "RoverCommand";
   
  Button r, b, f, l, s;
   
  private static final int REQUEST_ENABLE_BT = 1;
  private BluetoothAdapter btAdapter = null;
  private BluetoothSocket btSocket = null;
  private OutputStream outStream = null;
  
   
  // Well known SPP UUID
  private static final UUID MY_UUID =
      UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
 
  // Insert your server's MAC address
  private static String address = "00:12:12:03:18:56";
   
  /** Called when the activity is first created. */
  @Override
  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
 
    Log.d(TAG, "In onCreate()");
    
    setContentView(R.layout.main);
    
    r = (Button) findViewById(R.id.r);
    b = (Button) findViewById(R.id.b);
    l = (Button) findViewById(R.id.l);
    f = (Button) findViewById(R.id.f);
    s = (Button) findViewById(R.id.s);
    
    btAdapter = BluetoothAdapter.getDefaultAdapter();
    checkBTState();
 
    f.setOnClickListener(new OnClickListener() {
      public void onClick(View v) {
        sendData("F");
        Toast msg = Toast.makeText(getBaseContext(),
            "Going Forwards", Toast.LENGTH_SHORT);
        msg.show();
      }
    });
    
    l.setOnClickListener(new OnClickListener() {
        public void onClick(View v) {
          sendData("L");
          Toast msg = Toast.makeText(getBaseContext(),
              "Going Left", Toast.LENGTH_SHORT);
          msg.show();
        }
      });
    
    r.setOnClickListener(new OnClickListener() {
        public void onClick(View v) {
          sendData("R");
          Toast msg = Toast.makeText(getBaseContext(),
              "Going Back", Toast.LENGTH_SHORT);
          msg.show();
        }
      });
    
    s.setOnClickListener(new OnClickListener() {
        public void onClick(View v) {
          sendData("S");
          Toast msg = Toast.makeText(getBaseContext(),
              "Brake", Toast.LENGTH_SHORT);
          msg.show();
        }
      });
    
    b.setOnClickListener(new OnClickListener() {
      public void onClick(View v) {
        sendData("B");
        Toast msg = Toast.makeText(getBaseContext(),
            "Going Backwards", Toast.LENGTH_SHORT);
        msg.show();
      }
    });
  }
   
  @Override
  public void onResume() {
    super.onResume();
 
    Log.d(TAG, "...In onResume - Attempting client connect...");
   
    // Set up a pointer to the remote node using it's address.
    BluetoothDevice device = btAdapter.getRemoteDevice(address);
   
    // Two things are needed to make a connection:
    //   A MAC address, which we got above.
    //   A Service ID or UUID.  In this case we are using the
    //     UUID for SPP.
    try {
      btSocket = device.createRfcommSocketToServiceRecord(MY_UUID);
    } catch (IOException e) {
      errorExit("Bluetooth Connection Error", "In onResume() and socket create failed: " + e.getMessage() + ".");
    }
   
    // Discovery is resource intensive.  Make sure it isn't going on
    // when you attempt to connect and pass your message.
    btAdapter.cancelDiscovery();
   
    // Establish the connection.  This will be blocked until it connects.
    Log.d(TAG, "...Connecting...");
    try {
      btSocket.connect();
      Log.d(TAG, "...Connection established and data link opened...");
    } catch (IOException e) {
      try {
        btSocket.close();
      } catch (IOException e2) {
        errorExit("Bluetooth Connection Error", "In onResume() and unable to close socket during connection failure" + e2.getMessage() + ".");
      }
    }
     
    // Create a data stream so we can talk to server.
    Log.d(TAG, "...Creating Socket to send signals...");
 
    try {
      outStream = btSocket.getOutputStream();
    } catch (IOException e) {
      errorExit("Connection Error", "In onResume() and output stream creation failed:" + e.getMessage() + ".");
    }
  }
 
  @Override
  public void onPause() {
    super.onPause();
 
    Log.d(TAG, "...In onPause()...");
 
    if (outStream != null) {
      try {
        outStream.flush();
      } catch (IOException e) {
        errorExit("Connection Error", "In onPause() and failed to flush output stream: " + e.getMessage() + ".");
      }
    }
 
    try     {
      btSocket.close();
    } catch (IOException e2) {
      errorExit("Connection Error", "In onPause() and failed to close socket." + e2.getMessage() + ".");
    }
  }
   
  private void checkBTState() {
    // Check for Bluetooth support and then check to make sure it is turned on

    if(btAdapter==null) {
      errorExit("Connection Error", "Bluetooth Not supported. Aborting.");
    } else {
      if (btAdapter.isEnabled()) {
        Log.d(TAG, "...Bluetooth is enabled...");
      } else {
        //Prompt user to turn on Bluetooth
        Intent enableBtIntent = new Intent(btAdapter.ACTION_REQUEST_ENABLE);
        startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
      }
    }
  }
 
  private void errorExit(String title, String message){
    Toast msg = Toast.makeText(getBaseContext(),
        title + " - " + message, Toast.LENGTH_SHORT);
    msg.show();
    finish();
  }
 
  private void sendData(String message) {
    byte[] msgBuffer = message.getBytes();
 
    Log.d(TAG, "...Sending data: " + message + "...");
 
    try {
      outStream.write(msgBuffer);
    } catch (IOException e) {
      String msg = "In onResume() and an exception occurred during write: " + e.getMessage();
      if (address.equals("00:00:00:00:00:00"))
        msg = msg + ".\n\nUpdate your server address from 00:00:00:00:00:00 to the correct address on line 34 in the java code and then recompile the application";
      msg = msg +  ".\n\nCheck that the SPP UUID: " + MY_UUID.toString() + " exists on server.\n\n";
       
      errorExit("Connection Error", msg);      
    }
  }
}

   