package com.ec.ds
{
	import flash.utils.ByteArray;

	public class IndexedImage
	{
		private var _row:int;
		private var _column:int;
		private var _name:String = null;
		private var _data:ByteArray = null;
	
		
		public function get row():int
		{
			return _row;
		}

		public function set row(value:int):void
		{
			_row = value;
		}

		public function get column():int
		{
			return _column;
		}

		public function set column(value:int):void
		{
			_column = value;
		}

		public function get name():String
		{
			return _name;
		}
		public function set name(value:String):void
		{
			_name = value;
		}
		public function get data():ByteArray
		{
			return _data;
		}
		
		public function set data(value:ByteArray):void
		{
			_data = value;
		}
		
		public function IndexedImage()
		{
		}

	}
}