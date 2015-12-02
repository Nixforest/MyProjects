package com.nixforest.todo_list;

import java.util.ArrayList;

import android.app.Activity;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

public class ToDoList extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_to_do_list);
		// Get references to UI widgets
		ListView myListView = (ListView)findViewById(R.id.myListView);
		final EditText myEditText = (EditText)findViewById(R.id.myEditText);
		// Create the array list of to do items
		final ArrayList<String> todoItems = new ArrayList<String>();
		// Create the array adapter to bind the array to the listview
		final ArrayAdapter<String> aa;
		aa = new ArrayAdapter<>(this,
				android.R.layout.simple_list_item_1,
				todoItems);
		// Bind the array adapter to the listView
		myListView.setAdapter(aa);
		myEditText.setOnKeyListener(new OnKeyListener() {
			
			@Override
			public boolean onKey(View v, int keyCode, KeyEvent event) {
				if (event.getAction() == KeyEvent.ACTION_DOWN) {
					if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER) {
						if (!myEditText.getText().toString().isEmpty()) {
							todoItems.add(0, myEditText.getText().toString());
							aa.notifyDataSetChanged();
							myEditText.setText("");
							return true;
						}
					}
				}
				return false;
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.to_do_list, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
