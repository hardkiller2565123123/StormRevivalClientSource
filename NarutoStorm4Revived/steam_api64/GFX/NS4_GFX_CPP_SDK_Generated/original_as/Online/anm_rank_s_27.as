package result_main_fla
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol37")]
   public dynamic class anm_rank_s_27 extends MovieClip
   {
      
      public function anm_rank_s_27()
      {
         super();
         addFrameScript(0,this.frame1,6,this.frame7,25,this.frame26,69,this.frame70);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame7() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MENU_MODE_FIX);
      }
      
      internal function frame26() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_CHANGE);
      }
      
      internal function frame70() : *
      {
         this.stop();
      }
   }
}

