package com.ec.ds
{
	public class Manifect
	{
		private var _version:String = null;
		private var _copyright:String = null;
		private var _author:String = null;
		private var _createTime:String = null;
		private var _clip:Array = new Array();
		private var _width:int = 640;
		private var _height:int = 480;
		
		public function get width():int
		{
			return _width;
		}

		public function set width(value:int):void
		{
			_width = value;
		}

		public function get height():int
		{
			return _height;
		}

		public function set height(value:int):void
		{
			_height = value;
		}

		public function get version():String
		{
			return _version;
		}
		public function set version(value:String):void
		{
			_version = value;
		}
		public function get copyright():String
		{
			return _copyright;
		}
		
		public function set copyright(value:String):void
		{
			_copyright = value;
		}
		public function get author():String
		{
			return _author;
		}
		
		public function set author(value:String):void
		{
			_author = value;
		}
		public function get createTime():String
		{
			return _createTime;
		}
		
		public function set createTime(value:String):void
		{
			_createTime = value;
		}
		
		public function get clip():Array
		{
			return _clip;
		}
		
		public function set clip(value:Array):void
		{
			_clip = value;
		}
		
		public function Manifect()
		{
		}


	}
}