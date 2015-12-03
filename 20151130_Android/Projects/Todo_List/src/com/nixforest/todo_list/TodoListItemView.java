/**
 * Item list view.
 */
package com.nixforest.todo_list;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.widget.TextView;

/**
 * Item list view.
 * @author NguyenPT
 *
 */
public class TodoListItemView extends TextView {
	/**
	 * Margin painter.
	 */
	private Paint marginPaint;
	/**
	 * Line painter.
	 */
	private Paint linePaint;
	/**
	 * Paper color.
	 */
	private int paperColor;
	/**
	 * Margin size.
	 */
	private float margin;

	/**
	 * Constructor.
	 * @param context The current context.
	 * @param ats AttributeSet
	 * @param ds defStyleAttr
	 */
	public TodoListItemView(Context context, AttributeSet ats, int ds) {
		super(context, ats, ds);
		init();
	}

	/**
	 * Constructor.
	 * @param context The current context.
	 */
	public TodoListItemView(Context context) {
		super(context);
		init();
	}

	/**
	 * Constructor.
	 * @param context The current context.
	 * @param attrs AttributeSet
	 */
	public TodoListItemView(Context context, AttributeSet attrs) {
		super(context, attrs);
		init();
	}

	/**
	 * Initialize.
	 */
	private void init() {
		// Get a reference to our resource table.
		Resources myResource = getResources();
		// Create the paint brushes we will use in the onDraw method
		marginPaint = new Paint(Paint.ANTI_ALIAS_FLAG);
		marginPaint.setColor(myResource.getColor(R.color.notepad_margin));
		linePaint = new Paint(Paint.ANTI_ALIAS_FLAG);
		linePaint.setColor(myResource.getColor(R.color.notepad_lines));
		
		// Get the paper background color and the margin width
		paperColor = myResource.getColor(R.color.notepad_paper);
		margin = myResource.getDimension(R.dimen.notepad_margin);
	}

	/**
	 * Implement this to do your drawing.
	 * @param canvas the canvas on which the background will be drawn.
	 */
	@Override
	public void onDraw(Canvas canvas) {
		// Use the base TextView to render the text
		//super.onDraw(canvas);
		// Color as paper
		canvas.drawColor(paperColor);
		// Draw ruled lines
		canvas.drawLine(0,  0, getMeasuredHeight(), 0, linePaint);
		canvas.drawLine(0, getMeasuredHeight(), getMeasuredWidth(), getMeasuredHeight(), linePaint);
		// Draw margin
		canvas.drawLine(margin, 0, margin, getMeasuredHeight(), marginPaint);
		
		// Move the text across from the margin
		canvas.save();
		canvas.translate(margin, 0);
		// Use the TextView to render the text
		super.onDraw(canvas);
		canvas.restore();
	}
}
