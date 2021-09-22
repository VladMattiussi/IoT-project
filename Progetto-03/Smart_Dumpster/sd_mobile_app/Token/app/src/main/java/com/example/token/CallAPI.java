package com.example.token;

import android.os.AsyncTask;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;

public class CallAPI extends AsyncTask<String, String, String> {
    public CallAPI() {
        //set context variables if required
    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();
    }

    @Override
    protected String doInBackground(String... params) {
        URL urlString = null; // URL to call
        String data = null;
        //try {
            //data = new JSONObject().put(params[1], params[2]).toString();
      //  } catch (JSONException e) {
           // e.printStackTrace();
     //   }
        try {
            urlString = new URL(params[0]);
        } catch (MalformedURLException e) {
            e.printStackTrace();
        }
        try {
            return doGet(urlString);
        } catch (IOException e) {
            e.printStackTrace();
        }

       // try {
           // return doPost(urlString,data.getBytes());
  //     } catch (IOException e) {
        //    e.printStackTrace();
        return "ciao";
    }

    public String readStream(InputStream stream, int maxReadSize)
            throws IOException, UnsupportedEncodingException {
        final StringBuilder response = new StringBuilder();

        try (BufferedReader reader = new BufferedReader(new InputStreamReader(stream))) {
            String line;
            while ((line = reader.readLine()) != null) {
                response.append(line);
            }
        }

        return response.toString();
    }

    private String doGet(final URL url) throws IOException{
        HttpURLConnection c = (HttpURLConnection) url.openConnection();
        c.setRequestMethod("GET");

        if(c.getResponseCode() == HttpURLConnection.HTTP_OK)
            return readStream(c.getInputStream(),2048);
        else{
            return "error";
        }
    }

    private String doPost(final URL url,final byte[] payload) throws IOException{
        final HttpURLConnection c = (HttpURLConnection) url.openConnection();
            c.setRequestMethod("POST");
            c.setDoOutput(true);
            c.getOutputStream().write(payload);

        if(c.getResponseCode() == HttpURLConnection.HTTP_OK ) {
            return readStream(c.getInputStream(), 2048);
        }
        else {
            return "errore";
        }


    }


}
