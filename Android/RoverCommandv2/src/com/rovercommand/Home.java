package com.rovercommand;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;


public class Home extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.home);
       
        Button b = (Button) findViewById(R.id.start);
        b.setOnClickListener(new View.OnClickListener() {
           public void onClick(View arg0) {
           Intent i = new Intent(Home.this, Main.class);
           startActivity(i);
           }
        });
        Button b1 = (Button) findViewById(R.id.btn1);
        b1.setOnClickListener(new View.OnClickListener() {
           public void onClick(View arg0) {
           Intent i = new Intent(Home.this, About.class);
           startActivity(i);
           }
        });
        Button b2 = (Button) findViewById(R.id.btn2);
        b2.setOnClickListener(new View.OnClickListener() {
           public void onClick(View arg0) {
           Intent i = new Intent(Home.this, Config.class);
           startActivity(i);
           }
        });
    }
}