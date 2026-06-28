package script.eula_pp
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol2")]
   public class nut_eula extends MovieClip
   {
      
      public var dmy_img:nut_tex00;
      
      public var mc_page:anm_page;
      
      private var m_page:MovieClip = null;
      
      private var m_dmy:nut_tex00 = null;
      
      private var m_eulaImage:ExtendLoader = null;
      
      private var m_callbackFunc:Function = null;
      
      public function nut_eula()
      {
         super();
         addFrameScript(4,this.frame5,9,this.frame10);
         this.m_page = this["mc_page"];
         this.m_dmy = this["dmy_img"];
         this.m_dmy.Initialize();
         trace(this.m_dmy);
      }
      
      public function SetCallbackOpendFunc(param1:Function) : *
      {
         this.m_callbackFunc = param1;
      }
      
      public function SetPage(param1:int, param2:int) : *
      {
         this.m_page.SetPage(param1,param2);
      }
      
      public function SetImage(param1:String) : *
      {
         if(param1 == "")
         {
            return;
         }
         this.m_dmy.AttachImage(param1);
      }
      
      private function CallBackOpened() : *
      {
         this.m_callbackFunc();
      }
      
      internal function frame5() : *
      {
         this.CallBackOpened();
         this.stop();
      }
      
      internal function frame10() : *
      {
         this.CallBackOpened();
         this.stop();
      }
   }
}

