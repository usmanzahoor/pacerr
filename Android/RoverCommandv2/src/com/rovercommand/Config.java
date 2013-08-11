package com.rovercommand;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;


public class Config extends Activity {
	
	 EditText editText1, editText2, editText3, editText4, editText5, editText6;
	 Button setconfig, fbtn, bbtn, lbtn, rbtn, sbtn;
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.config);
        
        editText1 = (EditText)findViewById(R.id.editText1);
        editText2 = (EditText)findViewById(R.id.editText2);
        editText3 = (EditText)findViewById(R.id.editText3);
        editText4 = (EditText)findViewById(R.id.editText4));
        editText5 = (EditText)findViewById(R.id.editText5);
        editText6 = (EditText)findViewById(R.id.editText6);
        setconfig = (Button)findViewById(R.id.setconfig);
        fbtn = (Button)findViewById(R.id.fbtn);
        bbtn = (Button)findViewById(R.id.bbtn);
        lbtn = (Button)findViewById(R.id.lbtn);
        rbtn = (Button)findViewById(R.id.rbtn);
        sbtn = (Button)findViewById(R.id.sbtn);
       
        setconfig.setOnClickListener(setconfigOnClickListener);
        fbtn.setOnClickListener(fbtnOnClickListener);
        bbtn.setOnClickListener(bbtnOnClickListener);
        lbtn.setOnClickListener(lbtnOnClickListener);
        rbtn.setOnClickListener(rbtnOnClickListener);
        sbtn.setOnClickListener(sbtnOnClickListener);
        
        
        Button start = (Button)findViewById(R.id.start);
        start.setOnClickListener(new Button.OnClickListener(){
    @Override
    public void onClick(View arg0) {
     // TODO Auto-generated method stub
     Intent intent = new Intent();
              intent.setClass(Config.this, Main.class);
              startActivity(intent);
    }});
       
        LoadPreferences();
    }
    
    Button.OnClickListener setconfigOnClickListener
    = new Button.OnClickListener(){

   @Override
   public void onClick(View arg0) {
    // TODO Auto-generated method stub
    SavePreferences("mac", editText1.getText().toString());
    LoadPreferences();
   }
    
   };
   
    Button.OnClickListener fbtnOnClickListener
    = new Button.OnClickListener(){

   @Override
   public void onClick(View arg0) {
    // TODO Auto-generated method stub
    SavePreferences("fwd", editText2.getText().toString());
    LoadPreferences();
   }
    
   };
  
   Button.OnClickListener bbtnOnClickListener
  = new Button.OnClickListener(){

   @Override
   public void onClick(View arg0) {
    // TODO Auto-generated method stub
    SavePreferences("bwd", editText3.getText().toString());
    LoadPreferences();
   }
 
   };

   Button.OnClickListener rbtnOnClickListener
    = new Button.OnClickListener(){

   @Override
   public void onClick(View arg0) {
    // TODO Auto-generated method stub
    SavePreferences("rgt", editText5.getText().toString());
    LoadPreferences();
   }
    
   };

   Button.OnClickListener lbtnOnClickListener
    = new Button.OnClickListener(){

   @Override
   public void onClick(View arg0) {
    // TODO Auto-generated method stub
    SavePreferences("lft", editText4.getText().toString());
    LoadPreferences();
   }
    
   };

   Button.OnClickListener sbtnOnClickListener
    = new Button.OnClickListener(){

   @Override
   public void onClick(View arg0) {
    // TODO Auto-generated method stub
    SavePreferences("stp", editText6.getText().toString());
    LoadPreferences();
   }
    
   };

   private void SavePreferences(String key, String value){
    SharedPreferences sharedPreferences = getSharedPreferences("PREFS", MODE_PRIVATE);
    SharedPreferences.Editor editor = sharedPreferences.edit();
    editor.putString(key, value);
    editor.commit();
   }
  
   private void LoadPreferences(){
    SharedPreferences sharedPreferences = getSharedPreferences("PREFS", MODE_PRIVATE);
    String fwd = sharedPreferences.getString("fwd", "");
    String bwd = sharedPreferences.getString("bwd", "");
    String rgt = sharedPreferences.getString("rgt", "");
    String lft = sharedPreferences.getString("lft", "");
    String stp = sharedPreferences.getString("stp", "");
    String mac = sharedPreferences.getString("mac", "");

       
        Button b = (Button) findViewById(R.id.btn7);
        b.setOnClickListener(new View.OnClickListener() {
           public void onClick(View arg0) {
           Intent i = new Intent(Config.this, Home.class);
           startActivity(i);
           }
        });
    }
}