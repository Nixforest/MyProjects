package com.nixforest.contactpicker;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.provider.Contacts;
import android.provider.ContactsContract;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.database.Cursor;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ListView;
import android.widget.SimpleCursorAdapter;


public class ContactPicker extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_contact_picker);
        Intent intent = getIntent();
        String dataPath = intent.getData().toString();
        final Uri data = Uri.parse(dataPath + "people/");
        final Cursor cursor = getContentResolver().query(data, null, null, null, null);
        //String[] from = new String[] {Contacts.People.NAME};
        String[] from = new String[] {ContactsContract.Contacts.DISPLAY_NAME};
        int[] to = new int[] {R.id.itemTextView};
        SimpleCursorAdapter adapter = new SimpleCursorAdapter(this,
                R.layout.listitemlayout,
                cursor, from, to, 1);
        ListView lv = (ListView)findViewById(R.id.contactListView);
        lv.setAdapter(adapter);
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                // Move the cursor to the selected item
                cursor.moveToPosition(position);
                // Extract the row id
                int rowId = cursor.getInt(cursor.getColumnIndexOrThrow("_id"));
                // Construct the result URI
                Uri outUri = Uri.parse(data.toString() + rowId);
                Intent outData = new Intent();
                outData.setData(outUri);
                setResult(Activity.RESULT_OK, outData);
                finish();
            }
        });
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_contact_picker, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
