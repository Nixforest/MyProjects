package com.nixforest.todo_list;

import java.util.ArrayList;

import android.app.Activity;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.KeyEvent;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.ListView;

public class ToDoList extends Activity {
	static final private int ADD_NEW_TODO = Menu.FIRST;
	static final private int REMOVE_TODO = Menu.FIRST + 1;
	private boolean addingNew = false;
	private ListView myListView;
	private EditText myEditText;
	private ArrayList<String> todoItems;
	private ArrayAdapter<String> aa;
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_to_do_list);
		// Get references to UI widgets
		myListView = (ListView)findViewById(R.id.myListView);
		myEditText = (EditText)findViewById(R.id.myEditText);
		// Create the array list of to do items
		todoItems = new ArrayList<String>();
		// Create the array adapter to bind the array to the listview
		aa = new ArrayAdapter<>(this,
				//android.R.layout.simple_list_item_1,
				R.layout.todolist_item,
				todoItems);
		// Bind the array adapter to the listView
		myListView.setAdapter(aa);
		myEditText.setOnKeyListener(new View.OnKeyListener() {
			
			@Override
			public boolean onKey(View arg0, int arg1, KeyEvent arg2) {
				if (arg2.getAction() == KeyEvent.ACTION_DOWN) {
					if (arg1 == KeyEvent.KEYCODE_ENTER) {
						if (!myEditText.getText().toString().isEmpty()) {
							todoItems.add(0, myEditText.getText().toString());
							aa.notifyDataSetChanged();
							//myEditText.setText("");
							cancelAdd();
							return true;
						}
					}
				}
				return false;
			}
		});
		registerForContextMenu(myListView);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		//getMenuInflater().inflate(R.menu.to_do_list, menu);
		super.onCreateOptionsMenu(menu);
		// Create and add new menu items
		MenuItem itemAdd = menu.add(0, ADD_NEW_TODO, Menu.NONE, R.string.add_new);
		MenuItem itemRem = menu.add(0, REMOVE_TODO, Menu.NONE, R.string.remove);
		// Assign icons
		itemAdd.setIcon(R.drawable.add);
		itemRem.setIcon(R.drawable.close);
		
		// Allocate shortcuts to each of them
		itemAdd.setShortcut('0', 'a');
		itemRem.setShortcut('1', 'r');
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		//int id = item.getItemId();
		//if (id == R.id.action_settings) {
		//	return true;
		//}
		super.onOptionsItemSelected(item);
		int idx = myListView.getSelectedItemPosition();
		switch (item.getItemId()) {
			case REMOVE_TODO: {
				if (addingNew) {
					cancelAdd();
				} else {
					removeItem(idx);
				}
				return true;
			}
			case ADD_NEW_TODO: {
				addNewItem();
				return true;
			}
			default: break;
		}
		return false;
	}
	private void cancelAdd() {
		addingNew = false;
		myEditText.setVisibility(View.GONE);
	}
	private void addNewItem() {
		addingNew = true;
		myEditText.setVisibility(View.VISIBLE);
		myEditText.requestFocus();
	}
	private void removeItem(int _index) {
		todoItems.remove(_index);
		aa.notifyDataSetChanged();
	}
	@Override
	public void onCreateContextMenu(ContextMenu menu,
			View v, ContextMenu.ContextMenuInfo menuInfo) {
		super.onCreateContextMenu(menu, v, menuInfo);
		menu.setHeaderTitle("Selected To Do Item");
		menu.add(0, REMOVE_TODO, Menu.NONE, R.string.remove);
	}
	@Override
	public boolean onPrepareOptionsMenu(Menu menu) {
		super.onPrepareOptionsMenu(menu);
		// Get references to UI widgets
		int idx = myListView.getSelectedItemPosition();
		String removeTitle = getString(addingNew ? R.string.cancel : R.string.remove);
		MenuItem removeItem = menu.findItem(REMOVE_TODO);
		removeItem.setTitle(removeTitle);
		removeItem.setVisible(addingNew || (idx > -1));
		return true;
	}
	@Override
	public boolean onContextItemSelected(MenuItem item) {
		super.onContextItemSelected(item);
		switch (item.getItemId()) {
		case REMOVE_TODO: {
			AdapterView.AdapterContextMenuInfo menuInfo;
			menuInfo = (AdapterView.AdapterContextMenuInfo)item.getMenuInfo();
			int idx = menuInfo.position;
			removeItem(idx);
			return true;
		}
		case ADD_NEW_TODO: {
			addNewItem();
			return true;
		}
		default: break;
	}
		return false;
	}
}
