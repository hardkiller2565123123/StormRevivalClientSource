package script.duel_free
{
   import flash.display.MovieClip;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class anm_mkr extends MovieClip
   {
      
      public var mc_mkr:MovieClip;
      
      public function anm_mkr()
      {
         super();
         addFrameScript(0,this.frame1,8,this.frame9);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame9() : *
      {
         stop();
      }
   }
}

