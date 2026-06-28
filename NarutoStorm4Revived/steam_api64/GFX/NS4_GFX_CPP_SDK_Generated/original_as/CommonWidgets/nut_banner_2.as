package script.net_banner
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.external.*;
   import flash.net.URLRequest;
   
   public class nut_banner extends MovieClip
   {
      
      private var my_loaderEx:ExtendLoader = new ExtendLoader();
      
      public function nut_banner()
      {
         super();
         stop();
      }
      
      public function Initialize() : *
      {
         var _loc1_:MovieClip = getChildByName("mc_event") as MovieClip;
         _loc1_.txt_event.visible = false;
         _loc1_.txt_period.visible = false;
         stop();
      }
      
      public function PlayInAnm() : *
      {
         gotoAndPlay("in");
      }
      
      public function PlayOutAnm() : *
      {
         gotoAndPlay("out");
      }
      
      public function SetPos(param1:Number, param2:Number) : *
      {
         this.x = param1;
         this.y = param2;
      }
      
      public function SetTextTitle(param1:String) : *
      {
         var _loc2_:MovieClip = getChildByName("mc_event") as MovieClip;
         _loc2_.txt_event.visible = true;
         _loc2_.txt_event.SetText(String(ExternalInterface.call("MessageConvert",param1)));
      }
      
      public function SetTextDay(param1:String) : *
      {
         var _loc2_:MovieClip = getChildByName("mc_event") as MovieClip;
         _loc2_.txt_period.visible = true;
         _loc2_.txt_period.SetText(param1);
      }
      
      public function setTitleBanner(param1:int) : *
      {
         var _loc2_:URLRequest = null;
         var _loc3_:Array = ["../net_banner/tex_banner/net_bnr02.xfbin","../net_banner/tex_banner/net_bnr03.xfbin","../net_banner/tex_banner/net_bnr04.xfbin","../net_banner/tex_banner/net_bnr05.xfbin","../net_banner/tex_banner/net_bnr06.xfbin","../net_banner/tex_banner/net_bnr07.xfbin","../net_banner/tex_banner/net_bnr08.xfbin","../net_banner/tex_banner/net_bnr09.xfbin","../net_banner/tex_banner/net_bnr11.xfbin","../net_banner/tex_banner/net_bnr12.xfbin","../net_banner/tex_banner/net_bnr13.xfbin","../net_banner/tex_banner/net_bnr10.xfbin"];
         if(param1 == -2 || param1 == -3)
         {
            _loc2_ = new URLRequest("../net_banner/tex_banner/net_bnr01.xfbin");
         }
         else
         {
            _loc2_ = new URLRequest(_loc3_[param1]);
         }
         this.my_loaderEx.load(_loc2_);
         this.my_loaderEx.contentLoaderInfo.addEventListener(Event.COMPLETE,this.attachTitle);
      }
      
      public function clearTitleEx() : void
      {
         this.my_loaderEx.unload();
      }
      
      private function attachTitle(param1:Event) : void
      {
         var _loc2_:* = getChildByName("dmy_banner") as MovieClip;
         if(_loc2_ != null)
         {
            this.my_loaderEx.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            _loc2_.addChild(this.my_loaderEx);
            this.PlayInAnm();
         }
      }
   }
}

