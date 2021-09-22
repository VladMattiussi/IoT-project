package com.example.token;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentTransaction;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.concurrent.ExecutionException;

public class Fragment_main extends Fragment {
    private static final int ACTIVITY_CONNECTION = 1;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable
            ViewGroup container, @Nullable Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_connection, container, false);
        final TextView text = view.findViewById(R.id.textView);
        text.setMovementMethod(new ScrollingMovementMethod());
        final Activity activity = getActivity();
        if(activity != null) {
            view.findViewById(R.id.button2).setOnClickListener(new View.OnClickListener() {
                String ciao;
                @Override
                public void onClick(View v) {
                    final CallAPI connessione = new CallAPI();
                    JSONObject explrObject = null;
                    JSONArray jsonArray = null;
                    try {
                        ciao = connessione.execute("https://ba87ba3c.ngrok.io/Iot/file/dati.json").get();
                        try {
                            JSONObject jsnobject = new JSONObject(ciao);
                            jsonArray = jsnobject.getJSONArray("db");
                            explrObject = jsonArray.getJSONObject(0);
                        } catch (JSONException e) {
                            e.printStackTrace();
                        }
                    } catch (ExecutionException e) {
                        e.printStackTrace();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    try {
                        if(0 == ("available".compareTo(explrObject.getString("state")))) {
                            text.setText("true");
                            replaceFragment(new Bluetooth_fragment());
                        }
                        else {
                            text.setText("false");
                        }
                    } catch (JSONException e) {
                        e.printStackTrace();
                    }
                    //activity.setResult(RESULT_OK);
                    //activity.finish();
                }
            });
        }
        return view;
    }
    private void replaceFragment(Fragment fragment) {
        FragmentTransaction transaction = getFragmentManager().beginTransaction();
// Replace whatever is in the fragment_container view with this fragment,
// and add the transaction to the back stack so the user can navigate back
        transaction.replace(R.id.fragment_container, fragment);
// Commit the transaction
        transaction.commit();
    }
}
