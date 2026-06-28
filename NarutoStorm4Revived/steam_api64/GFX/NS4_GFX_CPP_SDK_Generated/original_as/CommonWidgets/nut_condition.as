package script.freebtl_course
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol22")]
   public dynamic class nut_condition extends MovieClip
   {
      
      public var mc_char_bg:MovieClip;
      
      public var mc_condition_win:MovieClip;
      
      public function nut_condition()
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

