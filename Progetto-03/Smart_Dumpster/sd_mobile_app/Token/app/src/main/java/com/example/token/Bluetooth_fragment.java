package com.example.token;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import java.util.UUID;

import btlib.BluetoothChannel;
import btlib.BluetoothUtils;
import btlib.ConnectToBluetoothServerTask;
import btlib.ConnectionTask;
import btlib.RealBluetoothChannel;
import btlib.exceptions.BluetoothDeviceNotFound;
import com.example.token.utils.*;


public class Bluetooth_fragment extends Fragment {

    private BluetoothChannel btChannel;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        final View view = inflater.inflate(R.layout.fragment_bluetooth, container, false);
        final Activity activity = getActivity();

        final BluetoothAdapter btAdapter = BluetoothAdapter.getDefaultAdapter();

        if(btAdapter != null && !btAdapter.isEnabled()){
            startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), C.bluetooth.ENABLE_BT_REQUEST);
        }

        initUI(view);


        return view;
    }

    private void initUI(final View view) {
        view.findViewById(R.id.connectBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                try {
                    connectToBTServer(view);
                } catch (BluetoothDeviceNotFound bluetoothDeviceNotFound) {
                    bluetoothDeviceNotFound.printStackTrace();
                }
            }
        });

        view.findViewById(R.id.sendBtn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = ((EditText) view.findViewById(R.id.editText)).getText().toString();
                btChannel.sendMessage(message);
                ((EditText) view.findViewById(R.id.editText)).setText("");

            }
        });

        view.findViewById(R.id.buttonA).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = "A";
                btChannel.sendMessage(message);
                ((EditText) view.findViewById(R.id.editText)).setText("");
            }
        });

        view.findViewById(R.id.buttonB).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = "B";
                btChannel.sendMessage(message);
                ((EditText) view.findViewById(R.id.editText)).setText("");
            }
        });

        view.findViewById(R.id.buttonC).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = "C";
                btChannel.sendMessage(message);
                ((EditText) view.findViewById(R.id.editText)).setText("");
            }
        });

        view.findViewById(R.id.Extend).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String message = "E";
                btChannel.sendMessage(message);
                ((EditText) view.findViewById(R.id.editText)).setText("");
            }
        });
    }

    @Override
    public void onStop() {
        super.onStop();

        btChannel.close();
    }

    @Override
    public void onActivityResult(final int requestCode, final int resultCode, @Nullable final Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == -1) {
            Log.d(C.APP_LOG_TAG, "Bluetooth enabled!");
        }

        if (requestCode == C.bluetooth.ENABLE_BT_REQUEST && resultCode == 0) {
            Log.d(C.APP_LOG_TAG, "Bluetooth not enabled!");
        }
    }

    private void connectToBTServer(final View view) throws BluetoothDeviceNotFound {
        final BluetoothDevice serverDevice = BluetoothUtils.getPairedDeviceByName(C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME);

        final UUID uuid = BluetoothUtils.getEmbeddedDeviceDefaultUuid();
        //final UUID uuid = BluetoothUtils.generateUuidFromString(C.bluetooth.BT_SERVER_UUID);

        new ConnectToBluetoothServerTask(serverDevice, uuid, new ConnectionTask.EventListener() {
            @Override
            public void onConnectionActive(final BluetoothChannel channel) {

                ((TextView) view.findViewById(R.id.statusLabel)).setText(String.format("Status : connected to server on device %s",
                        serverDevice.getName()));

                view.findViewById(R.id.connectBtn).setEnabled(false);

                btChannel = channel;
                btChannel.registerListener(new RealBluetoothChannel.Listener() {
                    @Override
                    public void onMessageReceived(String receivedMessage) {
                        ((TextView) view.findViewById(R.id.chatLabel)).append(String.format("> [RECEIVED from %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                receivedMessage));
                    }

                    @Override
                    public void onMessageSent(String sentMessage) {
                        ((TextView) view.findViewById(R.id.chatLabel)).append(String.format("> [SENT to %s] %s\n",
                                btChannel.getRemoteDeviceName(),
                                sentMessage));
                    }
                });
            }

            @Override
            public void onConnectionCanceled() {
                ((TextView) view.findViewById(R.id.statusLabel)).setText(String.format("Status : unable to connect, device %s not found!",
                        C.bluetooth.BT_DEVICE_ACTING_AS_SERVER_NAME));
            }
        }).execute();
    }

    }
