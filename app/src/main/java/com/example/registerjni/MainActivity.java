package com.example.registerjni;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.example.dynamicregister.DynamicRegister;
import com.example.staticregister.StaticRegister;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
//    static {
//        System.loadLibrary("native-lib");
//    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        TextView tv2 = findViewById(R.id.sample_text2);
//        DynamicRegister.getString();
//        tv.setText(StaticRegister.stringFromJNI());

        tv.setText(DynamicRegister.stringFromJNIZ());
        tv2.setText(StaticRegister.stringFromJNI());
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public native String stringFromJNI();
}
