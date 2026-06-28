package script.freebtl_namebar
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.events.Event;
   import flash.net.URLRequest;
   
   public class nut_namebar01 extends MovieClip
   {
      
      public const PLAYER_1P:String = "1P";
      
      public const PLAYER_2P:String = "2P";
      
      public const PLAYER_3P:String = "3P";
      
      public const PLAYER_4P:String = "4P";
      
      public const PLAYER_5P:String = "5P";
      
      public const PLAYER_6P:String = "6P";
      
      public const PLAYER_7P:String = "7P";
      
      public const PLAYER_8P:String = "8P";
      
      public const PLAYER_COM:String = "COM";
      
      internal var attach_face:Boolean = false;
      
      internal var attach_name:Boolean = false;
      
      private var checkFace:Boolean = false;
      
      private var face_loader:ExtendLoader = new ExtendLoader();
      
      private var checkName:Boolean = false;
      
      private var my_loader:ExtendLoader = new ExtendLoader();
      
      public function nut_namebar01()
      {
         super();
         var _loc1_:MovieClip = getChildByName("txt_id") as MovieClip;
         if(_loc1_ != null)
         {
            _loc1_.visible = false;
         }
         addEventListener(Event.ENTER_FRAME,this.onEnterFrameCtrl);
      }
      
      public function setSelect(param1:Boolean, param2:Boolean) : void
      {
         if(param1)
         {
            if(param2)
            {
               gotoAndStop("on_curs");
            }
            else
            {
               gotoAndStop("on");
            }
         }
         else if(param2)
         {
            gotoAndStop("off_curs");
         }
         else
         {
            gotoAndStop("nomal");
         }
      }
      
      public function setDark(param1:Boolean, param2:Boolean) : void
      {
         if(param1)
         {
            if(param2)
            {
               gotoAndPlay("bad_in");
            }
            else
            {
               gotoAndPlay("dark_in");
            }
         }
         else if(param2)
         {
            gotoAndStop("bad");
         }
         else
         {
            gotoAndStop("dark");
         }
      }
      
      public function isEndDark() : Boolean
      {
         if(currentFrameLabel == "bad" || currentFrameLabel == "dark")
         {
            return true;
         }
         return false;
      }
      
      public function setDispFace(param1:Boolean) : void
      {
         var _loc2_:MovieClip = getChildByName("dmy_charicon_vs") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.visible = param1;
         }
      }
      
      public function setDispName(param1:Boolean) : void
      {
         var _loc2_:MovieClip = getChildByName("dmy_chara_name") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.visible = param1;
         }
      }
      
      public function setFace(param1:String) : void
      {
         var _loc2_:URLRequest = null;
         if(this.checkFace == false)
         {
            _loc2_ = new URLRequest("../charicon_vs/vs_" + param1 + ".xfbin");
            this.face_loader.load(_loc2_);
            this.checkFace = true;
         }
      }
      
      public function setName(param1:String) : void
      {
         var _loc2_:URLRequest = null;
         if(this.checkName == false)
         {
            _loc2_ = new URLRequest("../name_m/LANG/nm_" + param1 + ".xfbin");
            this.my_loader.load(_loc2_);
            this.checkName = true;
         }
      }
      
      private function onEnterFrameCtrl(param1:Event) : void
      {
         if(this.checkName)
         {
            if(this.my_loader.IsLoadedXfbin())
            {
               this.attachName();
               this.checkName = false;
            }
         }
         if(this.checkFace)
         {
            if(this.face_loader.IsLoadedXfbin())
            {
               this.attachFace();
               this.checkFace = false;
            }
         }
      }
      
      public function isLoad() : Boolean
      {
         if(this.checkName == false && this.checkFace == false)
         {
            return true;
         }
         return false;
      }
      
      public function clearFace() : void
      {
         var _loc1_:MovieClip = getChildByName("dmy_charicon_vs") as MovieClip;
         if(_loc1_ != null && this.attach_face == true)
         {
            this.attach_face = false;
            _loc1_.removeChild(this.face_loader);
            this.face_loader.unload();
         }
      }
      
      public function clearName() : void
      {
         var _loc1_:MovieClip = getChildByName("dmy_chara_name") as MovieClip;
         if(_loc1_ != null && this.attach_name == true)
         {
            this.attach_name = false;
            _loc1_.removeChild(this.my_loader);
            this.my_loader.unload();
         }
      }
      
      public function SetUserName(param1:String) : void
      {
         var _loc2_:MovieClip = getChildByName("txt_id") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.SetText(param1);
            _loc2_.visible = true;
         }
         if(Boolean(param1) && param1 != "")
         {
            this.clearName();
         }
      }
      
      private function attachFace() : void
      {
         var _loc1_:* = getChildByName("dmy_charicon_vs") as MovieClip;
         trace(_loc1_);
         if(_loc1_ != null)
         {
            this.attach_face = true;
            this.face_loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            _loc1_.addChild(this.face_loader);
         }
      }
      
      private function attachName() : void
      {
         var _loc1_:* = getChildByName("dmy_chara_name") as MovieClip;
         if(_loc1_ != null)
         {
            this.attach_name = true;
            _loc1_.visible = true;
            this.my_loader.SetPivot(ExtendLoader.CCD_PIVOT_CENTER_CENTER);
            _loc1_.addChild(this.my_loader);
         }
      }
      
      public function setPlayerIcon(param1:String) : void
      {
         var _loc2_:MovieClip = getChildByName("mc_player_s") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.gotoAndStop(param1);
         }
      }
      
      public function setPlayerIconVisible(param1:Boolean) : void
      {
         var _loc2_:MovieClip = getChildByName("mc_player_s") as MovieClip;
         if(_loc2_ != null)
         {
            _loc2_.visible = param1;
         }
      }
      
      public function setPlayerIconByNum(param1:Number) : void
      {
         var _loc2_:Array = ["COM","1P","2P","3P","4P","5P","6P","7P","8P"];
         var _loc3_:MovieClip = getChildByName("mc_player_s") as MovieClip;
         if(_loc3_ != null)
         {
            _loc3_.gotoAndStop(_loc2_[param1]);
         }
      }
   }
}

