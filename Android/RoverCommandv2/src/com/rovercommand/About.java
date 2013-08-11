package com.rovercommand;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;


public class About extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.about);
       
        Button b = (Button) findViewById(R.id.home);
        b.setOnClickListener(new View.OnClickListener() {
           public void onClick(View arg0) {
           Intent i = new Intent(About.this, Home.class);
           startActivity(i);
           }
        });
    }
}