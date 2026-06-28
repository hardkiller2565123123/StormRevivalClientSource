package start_event_fla
{
   import flash.display.MovieClip;
   import script.adv_msion.nut_msion_win;
   import script.xcmn_list.nut_list;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class nut_event_2 extends MovieClip
   {
      
      public var all_msion_win:nut_msion_win;
      
      public var all_list:nut_list;
      
      public function nut_event_2()
      {
         super();
         addFrameScript(2,this.frame3);
      }
      
      internal function frame3() : *
      {
         stop();
      }
   }
}

