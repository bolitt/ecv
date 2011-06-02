package com.ec.log
{
	import mx.utils.StringUtil;

	public class Logger
	{
		public static var TAG_DEBUG:String = "[DEBUG]";
		public static var TAG_INFO:String = "[INFO]";
		public static var TAG_WARNING:String = "[WARNING]";
		public static var TAG_ERROR:String = "[ERROR]";
		public static var TAG_FATAL:String = "[FATAL]";
		
		public static var writelnHandler:Function = null;  
		public var targetClassName:String = null;
		
		public function Logger(enforcer: LoggerEnforcer)
		{
		}
		
		public static function getInstance(className:String):Logger
		{
			var logger:Logger = new Logger(new LoggerEnforcer());
			logger.targetClassName = className;
			return logger;
		}
		
		public function debug(o:Object):void
		{
			writeln(TAG_DEBUG + targetClassName + ":" + o);
		}
		
		public function info(o:Object):void
		{
			writeln(TAG_INFO + targetClassName + ":" + o);
		}
		
		public function warning(o:Object):void
		{
			writeln(TAG_WARNING + targetClassName + ":" + o);	
		}
		
		public function error(o:Object):void
		{
			writeln(TAG_ERROR + targetClassName + ":" + o);
		}
		
		public function fatal(o:Object):void
		{
			writeln(TAG_FATAL + targetClassName + ":" + o);		
		}
		
		protected function writeln(o:Object):void
		{
			if (writelnHandler != null) 
			{
				var str:String = "" + o;
				writelnHandler(str);
			}
		}
	}
}
class LoggerEnforcer
{
	
}