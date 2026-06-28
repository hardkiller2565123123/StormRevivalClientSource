package script.start_top
{
   import flash.display.MovieClip;
   import script.xcmn_menu.nut_cursor_m;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol5")]
   public dynamic class nut_start_top extends MovieClip
   {
      
      public var all_cursor_b:nut_cursor_m;
      
      public var all_cursor_t:nut_cursor_m;
      
      public var all_list_00:MovieClip;
      
      public var all_list_01:MovieClip;
      
      public var all_list_02:MovieClip;
      
      public var all_list_03:MovieClip;
      
      public var all_list_04:MovieClip;
      
      public var all_list_05:MovieClip;
      
      public var all_list_06:MovieClip;
      
      public function nut_start_top()
      {
         super();
         addFrameScript(16,this.frame17,23,this.frame24);
      }
      
      internal function frame17() : *
      {
         stop();
      }
      
      internal function frame24() : *
      {
         stop();
      }
   }
}

