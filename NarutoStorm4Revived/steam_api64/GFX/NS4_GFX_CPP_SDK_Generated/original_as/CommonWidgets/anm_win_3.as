package shop_list_fla
{
   import flash.display.MovieClip;
   import script.xcmn_menu.nut_base;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol6")]
   public dynamic class anm_win_3 extends MovieClip
   {
      
      public var all_base:nut_base;
      
      public function anm_win_3()
      {
         super();
         addFrameScript(0,this.frame1);
      }
      
      internal function frame1() : *
      {
         this.stop();
      }
   }
}

