package script.freebtl_cp
{
   import flash.display.MovieClip;
   import script.msg_wins_l.nut_wins_l;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol58")]
   public dynamic class all_win_count extends MovieClip
   {
      
      public var all_wins_l:nut_wins_l;
      
      public function all_win_count()
      {
         super();
         addFrameScript(0,this.frame1,11,this.frame12);
      }
      
      internal function frame1() : *
      {
      }
      
      internal function frame12() : *
      {
         stop();
      }
   }
}

