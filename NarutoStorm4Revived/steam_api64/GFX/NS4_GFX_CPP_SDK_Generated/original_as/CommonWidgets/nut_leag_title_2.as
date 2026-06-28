package script.freebtl_leag
{
   import flash.display.MovieClip;
   import script.freebtl_msg_txt.nut_freebtl_set;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class nut_leag_title extends MovieClip
   {
      
      public var all_freebtl_set:nut_freebtl_set;
      
      public function nut_leag_title()
      {
         super();
         addFrameScript(5,this.frame6,10,this.frame11);
      }
      
      internal function frame6() : *
      {
         stop();
      }
      
      internal function frame11() : *
      {
         stop();
      }
   }
}

