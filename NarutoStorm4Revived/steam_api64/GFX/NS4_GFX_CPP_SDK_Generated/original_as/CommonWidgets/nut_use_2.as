package script.collect_skill
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol9")]
   public dynamic class nut_use extends MovieClip
   {
      
      public var mc_player:MovieClip;
      
      public var mc_win:MovieClip;
      
      public function nut_use()
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

