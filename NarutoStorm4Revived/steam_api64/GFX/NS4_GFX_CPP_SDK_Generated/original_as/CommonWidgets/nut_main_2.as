package script.option_keyboard
{
   import flash.display.MovieClip;
   import script.xcmn_unset.nut_scb_bg;
   import script.xct_deco1.nut_deco1;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol26")]
   public dynamic class nut_main extends MovieClip
   {
      
      public var all_main_bar_03:nut_main_bar_00;
      
      public var mc_set:MovieClip;
      
      public var all_main_bar_02:nut_main_bar_00;
      
      public var all_main_bar_01:nut_main_bar_00;
      
      public var all_main_bar_00:nut_main_bar_00;
      
      public var mc_title:MovieClip;
      
      public var mc_line_set1:MovieClip;
      
      public var all_deco1:nut_deco1;
      
      public var mc_win:MovieClip;
      
      public var mc_scb:nut_scb_bg;
      
      public var all_main_bar_07:nut_main_bar_00;
      
      public var all_main_bar_06:nut_main_bar_00;
      
      public var all_main_bar_05:nut_main_bar_00;
      
      public var all_main_bar_04:nut_main_bar_00;
      
      public function nut_main()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
      }
      
      internal function frame6() : *
      {
         stop();
         trace("TEstStop");
         trace(this.all_main_bar_02.visible);
         this.all_main_bar_02.visible = true;
      }
      
      internal function frame11() : *
      {
         stop();
      }
   }
}

