/**
 * Test provider controller.
 */
package com.nixforest.testprovidercontroller;

import java.util.Iterator;
import java.util.List;

import android.app.Activity;
import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

/**
 * Test provider controller activity.
 * @author NguyenPT
 *
 */
public class TestProviderController extends Activity {
	/**
	 * Location manager instance.
	 */
	private LocationManager locMan;
	
	/**
	 * Called when the activity is starting
	 * @param savedInstanceState If the activity is being re-initialized after
	 *                              previously being shut down then this Bundle
	 *                              contains the data it most recently supplied
	 *                              in onSaveInstanceState(Bundle).
	 *                              Note: Otherwise it is null.
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_test_provider_controller);
		String locContext = Context.LOCATION_SERVICE;
		locMan = (LocationManager)getSystemService(locContext);
		testProviders();
	}

	private void testProviders() {
		TextView tv = (TextView)findViewById(R.id.myTextView);
		StringBuilder sb = new StringBuilder("Enabled Providers:");
		List<String> lstProviders = locMan.getProviders(true);
		for (String provider : lstProviders) {
			locMan.requestLocationUpdates(provider, 1000, 0, new LocationListener() {
				
				@Override
				public void onStatusChanged(String arg0, int arg1, Bundle arg2) {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onProviderEnabled(String arg0) {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onProviderDisabled(String arg0) {
					// TODO Auto-generated method stub
					
				}
				
				@Override
				public void onLocationChanged(Location arg0) {
					// TODO Auto-generated method stub
					
				}
			});
			sb.append("\n").append(provider).append(": ");
			Location location = locMan.getLastKnownLocation(provider);
			if (location != null) {
				double lat = location.getLatitude();
				double lng = location.getLongitude();
				sb.append(lat).append(", ").append(lng);
			} else {
				sb.append("No location");
			}
		}
		tv.setText(sb);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.test_provider_controller, menu);
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
