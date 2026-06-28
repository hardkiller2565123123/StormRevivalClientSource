package result_main_fla
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol63")]
   public dynamic class anm_rank_a_38 extends MovieClip
   {
      
      public function anm_rank_a_38()
      {
         super();
         addFrameScript(0,this.frame1,6,this.frame7,30,this.frame31,37,this.frame38);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame7() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MENU_MODE_FIX);
      }
      
      internal function frame31() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_CHANGE);
      }
      
      internal function frame38() : *
      {
         this.stop();
      }
   }
}

