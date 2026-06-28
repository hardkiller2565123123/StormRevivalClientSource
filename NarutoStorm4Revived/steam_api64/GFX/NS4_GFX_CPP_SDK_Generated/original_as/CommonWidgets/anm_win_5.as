package collect_skill_fla
{
   import flash.display.MovieClip;
   import script.collect_cmn.nut_win_tab;
   import script.collect_cmn.nut_win_title;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol8")]
   public dynamic class anm_win_5 extends MovieClip
   {
      
      public var mc_win1:nut_win_tab;
      
      public var mc_win2:MovieClip;
      
      public var mc_win3:nut_win_title;
      
      public function anm_win_5()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,2,this.frame3);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         stop();
      }
      
      internal function frame3() : *
      {
         stop();
      }
   }
}

